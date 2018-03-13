#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include "BTexture.h"
#include "BTimer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int JOYSTICK_DEAD_ZONE = 8000;

bool init(void);
bool loadMedia(void);
void destroy(void);

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
BTexture *gFPSTextTexture = NULL;
TTF_Font *gFont = NULL;

bool init() {
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_Image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                
                if(TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    
    gFont = TTF_OpenFont("Hello/lazy.ttf", 28);
    if(gFont == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    } else {
        gFPSTextTexture = BTexture_create();
    }
    
    return success;
}

void destroy() {
    BTexture_destroy(gFPSTextTexture);
    
    TTF_CloseFont(gFont);
    gFont = NULL;
    
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
    if(!init()) {
        printf("Failed to initialize!\n");
    } else {
        if(!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;
            SDL_Color textColor = {0, 0, 0, 255};
            BTimer *fpsTimer = BTimer_create();
            char timeText[1024];
            int countedFrames = 0;
            BTimer_start(fpsTimer);
            while(!quit) {
                SDL_Event e;
                while(SDL_PollEvent(&e) != 0) {
                    if(e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                
                float avgFPS = countedFrames / (BTimer_getTicks(fpsTimer) / 1000.f);
                if(avgFPS > 2000000) {
                    avgFPS = 0;
                }
                
                snprintf(timeText, sizeof(timeText), "Average Frames Per Second %f", avgFPS);
                if(!BTexture_loadFromRenderedText(gFPSTextTexture, gRenderer, gFont, timeText, textColor)) {
                    printf("Unable to render FPS texture!\n");
                }
                
                SDL_RenderClear(gRenderer);
                
                BTexture_render(gFPSTextTexture, gRenderer, (SCREEN_WIDTH - BTexture_getWidth(gFPSTextTexture)) / 2, (SCREEN_HEIGHT - BTexture_getHeight(gFPSTextTexture)) / 2, NULL, 0, NULL, SDL_FLIP_NONE);
                
                SDL_RenderPresent(gRenderer);
                countedFrames++;
            }
            BTimer_destroy(fpsTimer);
        }
    }
    destroy();
    return 0;
}

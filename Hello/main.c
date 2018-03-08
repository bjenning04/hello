#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "BTexture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init(void);
bool loadMedia(void);
void destroy(void);

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
BTexture *gArrowTexture;

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
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    
    gArrowTexture = BTexture_create();
    if(!BTexture_loadFromFile(gArrowTexture, gRenderer, "Hello/arrow.png")) {
        printf("Failed to load walking animation texture\n");
        success = false;
    }
    
    return success;
}

void destroy() {
    BTexture_destroy(gArrowTexture);
    
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    
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
            double degrees = 0;
            SDL_RendererFlip flipType = SDL_FLIP_NONE;
            while(!quit) {
                SDL_Event e;
                while(SDL_PollEvent(&e) != 0) {
                    if(e.type == SDL_QUIT) {
                        quit = true;
                    } else if(e.type == SDL_KEYDOWN) {
                        switch(e.key.keysym.sym) {
                            case SDLK_a:
                                degrees -= 60;
                                break;
                            case SDLK_d:
                                degrees += 60;
                                break;
                            case SDLK_q:
                                flipType = SDL_FLIP_HORIZONTAL;
                                break;
                            case SDLK_w:
                                flipType = SDL_FLIP_NONE;
                                break;
                            case SDLK_e:
                                flipType = SDL_FLIP_VERTICAL;
                                break;
                        }
                    }
                }
                
                SDL_RenderClear(gRenderer);
                
                BTexture_render(gArrowTexture, gRenderer, (SCREEN_WIDTH - BTexture_getWidth(gArrowTexture)) / 2, (SCREEN_HEIGHT - BTexture_getHeight(gArrowTexture)) / 2, NULL, degrees, NULL, flipType);
                
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    destroy();
    return 0;
}

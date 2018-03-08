//
//  BTexture.c
//  Hello
//
//  Created by Jennings,Brad on 3/1/18.
//  Copyright © 2018 GingerSoft. All rights reserved.
//

#include "BTexture.h"
#include <SDL2_image/SDL_image.h>

struct btexture {
    SDL_Texture *texture;
    int width;
    int height;
};

void BTexture_init(BTexture *self) {
    self->texture = NULL;
    self->width = 0;
    self->height = 0;
}

BTexture *BTexture_create() {
    BTexture *result = (BTexture *) malloc(sizeof(BTexture));
    BTexture_init(result);
    return result;
}

void BTexture_reset(BTexture *self) {
    if(self->texture != NULL) {
        SDL_DestroyTexture(self->texture);
        BTexture_init(self);
    }
}

void BTexture_destroy(BTexture *self) {
    if(self) {
        BTexture_reset(self);
        free(self);
    }
}

bool BTexture_loadFromFile(BTexture *self, SDL_Renderer *renderer, char *path)  {
    BTexture_reset(self);
    
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path);
    if(loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        } else {
            self->width = loadedSurface->w;
            self->height = loadedSurface->h;
        }
        
        SDL_FreeSurface(loadedSurface);
    }
    
    self->texture = newTexture;
    return self->texture != NULL;
}

void BTexture_setColor(BTexture *self, Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(self->texture, red, green, blue);
}

void BTexture_setBlendMode(BTexture *self, SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(self->texture, blending);
}

void BTexture_setAlpha(BTexture *self, Uint8 alpha) {
    SDL_SetTextureAlphaMod(self->texture, alpha);
}

void BTexture_render(BTexture *self, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = { x, y, self->width, self->height };
    if(clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, self->texture, clip, &renderQuad, angle, center, flip);
}

int BTexture_getWidth(BTexture *self) {
    return self->width;
}

int BTexture_getHeight(BTexture *self) {
    return self->height;
}

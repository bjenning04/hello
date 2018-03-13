//
//  BButton.c
//  Hello
//
//  Created by Jennings,Brad on 3/10/18.
//  Copyright © 2018 GingerSoft. All rights reserved.
//

#include "BButton.h"
#include <stdbool.h>

struct bbutton {
    SDL_Rect button;;
    enum BButtonSprite currentSprite;
};

BButton *BButton_create(int x, int y, int width, int height) {
    BButton *result = (BButton *) malloc(sizeof(BButton));
    result->button.x = x;
    result->button.y = y;
    result->button.w = width;
    result->button.h = height;
    result->currentSprite = BUTTON_SPRITE_MOUSE_OUT;
    return result;
}

void BButton_destroy(BButton *self) {
    if(self) {
        free(self);
    }
}

void BButton_handleEvent(BButton *self, SDL_Event *e) {
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x;
        int y;
        SDL_GetMouseState(&x, &y);
        
        bool inside = true;
        if(x < self->button.x || x > self->button.x + self->button.w || y < self->button.y || y > self->button.y + self->button.h) {
            inside = false;
        }
        
        if(!inside) {
            self->currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            switch(e->type) {
                case SDL_MOUSEMOTION:
                    self->currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    self->currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    self->currentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

void BButton_render(BButton *self, SDL_Renderer *renderer, BTexture *spriteSheet, SDL_Rect clips[]) {
    BTexture_render(spriteSheet, renderer, self->button.x, self->button.y, &clips[self->currentSprite], 0, NULL, SDL_FLIP_NONE);
}

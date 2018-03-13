//
//  BButton.h
//  Hello
//
//  Created by Jennings,Brad on 3/10/18.
//  Copyright © 2018 GingerSoft. All rights reserved.
//

#ifndef BButton_h
#define BButton_h

#include "BTexture.h"
#include <SDL2/SDL.h>

enum BButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

struct bbutton;
typedef struct bbutton BButton;

BButton *BButton_create(int x, int y, int width, int height);
void BButton_destroy(BButton *self);
void BButton_handleEvent(BButton *self, SDL_Event *e);
void BButton_render(BButton *self, SDL_Renderer *renderer, BTexture *spriteSheet, SDL_Rect clips[]);

#endif /* BButton_h */

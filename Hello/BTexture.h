//
//  BTexture.h
//  Hello
//
//  Created by Jennings,Brad on 3/1/18.
//  Copyright © 2018 GingerSoft. All rights reserved.
//

#ifndef BTexture_h
#define BTexture_h

#include <stdbool.h>
#include <SDL2/SDL.h>

struct btexture;
typedef struct btexture BTexture;

BTexture *BTexture_create(void);
void BTexture_destroy(BTexture *self);
bool BTexture_loadFromFile(BTexture *self, SDL_Renderer *renderer, char *path);
void BTexture_setColor(BTexture *self, Uint8 red, Uint8 green, Uint8 blue);
void BTexture_setBlendMode(BTexture *self, SDL_BlendMode blending);
void BTexture_setAlpha(BTexture *self, Uint8 alpha);
void BTexture_render(BTexture *self, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip);
int BTexture_getWidth(BTexture *self);
int BTexture_getHeight(BTexture *self);

#endif /* BTexture_h */

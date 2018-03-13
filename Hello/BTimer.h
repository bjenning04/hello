//
//  BTimer.h
//  Hello
//
//  Created by Jennings,Brad on 3/11/18.
//  Copyright © 2018 GingerSoft. All rights reserved.
//

#ifndef BTimer_h
#define BTimer_h

#include <SDL2/SDL.h>
#include <stdbool.h>

struct btimer;
typedef struct btimer BTimer;

BTimer *BTimer_create(void);
void BTimer_destroy(BTimer *self);
void BTimer_start(BTimer *self);
void BTimer_stop(BTimer *self);
void BTimer_pause(BTimer *self);
void BTimer_unpause(BTimer *self);
Uint32 BTimer_getTicks(BTimer *self);
bool BTimer_isStarted(BTimer *self);
bool BTimer_isPaused(BTimer *self);

#endif /* BTimer_h */

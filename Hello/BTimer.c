//
//  BTimer.c
//  Hello
//
//  Created by Jennings,Brad on 3/11/18.
//  Copyright © 2018 GingerSoft. All rights reserved.
//

#include "BTimer.h"

struct btimer {
    Uint32 startTicks;
    Uint32 pausedTicks;
    bool paused;
    bool started;
};

BTimer *BTimer_create() {
    BTimer *result = (BTimer *) malloc(sizeof(BTimer));
    result->startTicks = 0;
    result->pausedTicks = 0;
    result->paused = false;
    result->started = false;
    return result;
}

void BTimer_destroy(BTimer *self) {
    if(self) {
        free(self);
    }
}

void BTimer_start(BTimer *self) {
    self->started = true;
    self->paused = false;
    self->startTicks = SDL_GetTicks();
    self->pausedTicks = 0;
}

void BTimer_stop(BTimer *self) {
    self->started = false;
    self->paused = false;
    self->startTicks = 0;
    self->pausedTicks = 0;
}

void BTimer_pause(BTimer *self) {
    if(self->started && !self->paused) {
        self->paused = true;
        self->pausedTicks = SDL_GetTicks() - self->startTicks;
        self->startTicks = 0;
    }
}

void BTimer_unpause(BTimer *self) {
    if(self->started && self->paused) {
        self->paused = false;
        self->startTicks = SDL_GetTicks() - self->pausedTicks;
        self->pausedTicks = 0;
    }
}

Uint32 BTimer_getTicks(BTimer *self) {
    Uint32 time = 0;
    if(self->started) {
        if(self->paused) {
            time = self->pausedTicks;
        } else {
            time = SDL_GetTicks() - self->startTicks;
        }
    }
    return time;
}

bool BTimer_isStarted(BTimer *self) {
    return self->started;
}

bool BTimer_isPaused(BTimer *self) {
    return self->paused && self->started;
}

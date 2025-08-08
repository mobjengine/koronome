/*
A raycasting-ryona video game.
Copyright (C) 2025  mobjengine

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <SDL.h>

#ifdef M_PI
#undef M_PI
#define M_PI (3.141592657)
#endif
#define DEG_TO_RAD(deg) ((deg) * (M_PI / 180.0f))
#define RAD_TO_DEG(rad) ((rad) * (180.0f / M_PI))
#define TAU (2.0f * M_PI)
#define SCREEN_WIDTH (320)
#define SCREEN_HEIGHT (200)

typedef struct {
    Uint64 now;
    Uint64 last;
    float time;
} delta_t;

extern SDL_Renderer *renderer;
extern const Uint8 *keyboard;
extern delta_t delta;

void draw_wall_slice(int x, float wallHeight, float sliceWidth, SDL_Surface *surface, int texX);
SDL_Surface* K_CreateSurfaceFromMemory(const void* data, size_t size);

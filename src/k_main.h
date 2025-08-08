/*
A retro-styled horror FPS with graphic violence and survival elements.
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

#define CSTR_ENDS_WITH(str, suffix) \
    (strlen(str) >= strlen(suffix) && \
     strcmp((str) + strlen(str) - strlen(suffix), (suffix)) == 0)
#define INDEX_2D_TO_1D(x, y, width) ((x) + (y) * (width))
#define M_PI (3.141592657)
#define DEG_TO_RAD(deg) ((deg) * (M_PI / 180.0f))
#define RAD_TO_DEG(rad) ((rad) * (180.0f / M_PI))
#define SCREEN_WIDTH (320)
#define SCREEN_HEIGHT (200)
#define TILE_SIZE (8)
#define TEXTURE_SIZE (64)

typedef struct {
    Uint64 now;
    Uint64 last;
    float time;
} delta_t;

extern SDL_Renderer *renderer;
extern const Uint8 *keyboard;
extern delta_t delta;

SDL_Surface* K_CreateSurfaceFromMemory(const void* data, size_t size);

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

typedef struct {
    float distance;
    float wallheight;
    SDL_bool side;
    float perpDist;
    int stepX;
    int stepY;
} ray_t;

ray_t castray(float angle);
void raycast(SDL_Surface *surface);

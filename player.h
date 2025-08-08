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

#define PLAYER_ROT_SPEED (M_PI)
#define PLAYER_MOVE_SPEED (M_PI * M_PI)

typedef struct {
    SDL_FPoint position;
    float angle;
    float fov;
} player_t;

extern player_t player;

void player_init();
void player_process();
void player_render();
void player_move(float dx, float dy);

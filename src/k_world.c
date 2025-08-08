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

#include "k_world.h"
#include "k_main.h"

Uint8 world[WORLD_WIDTH * WORLD_HEIGHT];

void K_WorldInit() {
    memset(world, 0, sizeof(world));
}

void K_WorldRender2D() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int x = 0;x < WORLD_WIDTH;x++) {
        for(int y = 0;y < WORLD_HEIGHT;y++) {
            if(world[INDEX_2D_TO_1D(x, y, WORLD_WIDTH)]) {
                SDL_Rect rect = {x*8,y*8,8,8};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

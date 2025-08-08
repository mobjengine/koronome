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

#include "world.h"
#include "koronome.h"

Uint8 world[WORLD_WIDTH * WORLD_HEIGHT] = {
    1,1,1,1,1,1,1,
    1,0,0,0,0,0,1,
    1,0,1,1,1,0,1,
    1,0,1,0,1,0,1,
    1,0,0,0,0,0,1,
    1,1,1,1,1,1,1
};

void world_render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int x = 0;x < WORLD_WIDTH;x++) {
        for(int y = 0;y < WORLD_HEIGHT;y++) {
            SDL_Rect dstrect = {
                x * 8,
                y * 8,
                8,
                8
            };

            if(world[y * WORLD_WIDTH + x])
            SDL_RenderDrawRect(renderer, &dstrect);
        }
    }
}

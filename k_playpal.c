/*
koronome - Raycasting dungeon crawler with grid-based movement.
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

#include "k_playpal.h"
#include "k_lump.h"

SDL_Palette *playpal;

void K_PlaypalInit() {
    SDL_Color colors[256];
    playpal = SDL_AllocPalette(256);
    
    const lump_t *l = K_LumpGet("playpal.pal");
    uint8_t d[l->size];
    K_LumpData(l, d);

    for(int i = 0;i < 256;i++) {
        colors[i].r = d[(i*3)+0];
        colors[i].g = d[(i*3)+1];
        colors[i].b = d[(i*3)+2];
        colors[i].a = 255;
    }

    SDL_SetPaletteColors(playpal, colors, 0, 256);
}

void K_PlaypalShutdown() {
    SDL_FreePalette(playpal);
}

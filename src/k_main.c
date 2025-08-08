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

#include <SDL.h>
#include <SDL_image.h>
#include "k_main.h"
#include "k_player.h"
#include "k_lump.h"
#include "k_world.h"

SDL_Renderer *renderer;
const Uint8 *keyboard;
delta_t delta;
SDL_Palette *playpal;

int main(int argc, const char **argv) {
    K_LumpInit(argc, argv);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("KORONOME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    keyboard = SDL_GetKeyboardState(NULL);

    /*Loading playpal*/ {
        lump_t *l = K_LumpGet("playpal.pal");
        Uint8 p[l->size];
        K_LumpData(l, p);

        SDL_Color colors[256];
        int ci = 0;
        for (int i = 0; i + 2 < l->size; i += 3) {
            memcpy(&colors[ci], &p[i], 3);
            colors[ci++].a = 255;
        }
        playpal = SDL_AllocPalette(256);
        SDL_SetPaletteColors(playpal, colors, 0, 256);
    }

    K_WorldInit();
    
    world[INDEX_2D_TO_1D(0, 0, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(1, 0, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(2, 0, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(3, 0, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(4, 0, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(5, 0, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(6, 0, WORLD_WIDTH)] = SDL_TRUE;

    world[INDEX_2D_TO_1D(0, 5, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(1, 5, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(2, 5, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(3, 5, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(4, 5, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(5, 5, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(6, 5, WORLD_WIDTH)] = SDL_TRUE;

    world[INDEX_2D_TO_1D(0, 1, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(0, 2, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(0, 3, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(0, 4, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(0, 5, WORLD_WIDTH)] = SDL_TRUE;

    world[INDEX_2D_TO_1D(6, 1, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(6, 2, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(6, 3, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(6, 4, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(6, 5, WORLD_WIDTH)] = SDL_TRUE;

    world[INDEX_2D_TO_1D(2, 2, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(3, 2, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(4, 2, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(2, 3, WORLD_WIDTH)] = SDL_TRUE;
    world[INDEX_2D_TO_1D(4, 3, WORLD_WIDTH)] = SDL_TRUE;

    K_PlayerInit();

    memset(&delta, 0, sizeof(delta_t));
    delta.now = SDL_GetPerformanceCounter();
    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    do {
        delta.last = delta.now;
        delta.now = SDL_GetPerformanceCounter();
        delta.time = (float)((delta.now - delta.last) / (float)SDL_GetPerformanceFrequency());

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = SDL_TRUE;
                    break;
            }
        }

        K_PlayerProcess();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        K_WorldRender2D();
        K_PlayerRender2D();
        SDL_RenderPresent(renderer);
    } while(!quit);

    SDL_FreePalette(playpal);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    K_LumpShutdown();

    return EXIT_SUCCESS;
}

SDL_Surface* K_CreateSurfaceFromMemory(const void* data, size_t size) {
    SDL_RWops* rw = SDL_RWFromConstMem(data, (int)size);
    if (!rw) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_RWFromConstMem failed: %s", SDL_GetError());
        return NULL;
    }
    SDL_Surface* surface = IMG_Load_RW(rw, 1);
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load_RW failed: %s", SDL_GetError());
        return NULL;
    }
    SDL_SetSurfacePalette(surface, playpal);
    return surface;
}

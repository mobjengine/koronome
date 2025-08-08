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

#include <SDL.h>
#include "koronome.h"
#include "player.h"
#include "world.h"
#include "ray.h"

SDL_Renderer *renderer;
const Uint8 *keyboard;
delta_t delta;

int main(int argc, const char **argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("KORONOME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    keyboard = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    memset(&delta, 0, sizeof(delta_t));
    delta.now = SDL_GetPerformanceCounter(),
    player_init();

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

        player_process();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        raycast();
        world_render();
        player_render();
        SDL_RenderPresent(renderer);
    } while(!quit);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void draw_wall_slice(int x, float wallHeight, float sliceWidth) {
    int startY = (SCREEN_HEIGHT / 2) - (wallHeight / 2);
    if (startY < 0) startY = 0;

    SDL_Rect rect = {
        .x = x * (int)sliceWidth,
        .y = startY,
        .w = (int)sliceWidth,
        .h = wallHeight
    };

    SDL_SetRenderDrawColor(renderer, 180, 0, 180, 255);
    SDL_RenderFillRect(renderer, &rect);
}

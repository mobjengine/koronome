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

#include "k_player.h"
#include "k_main.h"

player_t player;

void K_PlayerInit() {
    memset(&player, 0, sizeof(player_t));
    player.position = (SDL_FPoint){3.5f,3.5f};
}

void K_PlayerProcess() {
    return;
}

void K_PlayerRender() {
    SDL_FPoint p = {player.position.x * 8, player.position.y * 8};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, p.x, p.y);
}

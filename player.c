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

#include "player.h"
#include "koronome.h"

player_t player;

void player_init() {
    memset(&player, 0, sizeof(player_t));
    player.position = (SDL_FPoint){8,8};
}

void player_process() {
    if (keyboard[SDL_SCANCODE_A]) {
        player.angle -= PLAYER_ROT_SPEED * delta.time;
    }
    if (keyboard[SDL_SCANCODE_D]) {
        player.angle += PLAYER_ROT_SPEED * delta.time;
    }

    if (player.angle < 0) player.angle += TAU;
    else if (player.angle >= TAU) player.angle -= TAU;

    float dx = SDL_cosf(player.angle);
    float dy = SDL_sinf(player.angle);

    if (keyboard[SDL_SCANCODE_W]) {
        player.position.x += dx * PLAYER_MOVE_SPEED * delta.time;
        player.position.y += dy * PLAYER_MOVE_SPEED * delta.time;
    }
    if (keyboard[SDL_SCANCODE_S]) {
        player.position.x -= dx * PLAYER_MOVE_SPEED * delta.time;
        player.position.y -= dy * PLAYER_MOVE_SPEED * delta.time;
    }
}

void player_render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPointF(renderer, player.position.x, player.position.y);
}
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
#include "world.h"

player_t player;

void player_init() {
    memset(&player, 0, sizeof(player_t));
    player.position = (SDL_FPoint){3.5f,3.5f};
    player.angle = DEG_TO_RAD(90.0f);
    player.fov = M_PI / 3.0f;
}

void player_process() {
    float dx = 0.0f;
    float dy = 0.0f;
    float moveSpeed = PLAYER_MOVE_SPEED * delta.time;

    if (keyboard[SDL_SCANCODE_W]) {
        dx += SDL_cosf(player.angle) * moveSpeed;
        dy += SDL_sinf(player.angle) * moveSpeed;
    }
    if (keyboard[SDL_SCANCODE_S]) {
        dx -= SDL_cosf(player.angle) * moveSpeed;
        dy -= SDL_sinf(player.angle) * moveSpeed;
    }

    player_move(dx, dy);

    if (keyboard[SDL_SCANCODE_A]) {
        player.angle -= PLAYER_ROT_SPEED * delta.time;
    }
    if (keyboard[SDL_SCANCODE_D]) {
        player.angle += PLAYER_ROT_SPEED * delta.time;
    }

    if (player.angle < 0) player.angle += TAU;
    else if (player.angle >= TAU) player.angle -= TAU;
}

void player_render() {
    SDL_Surface *s = SDL_LoadBMP("p.bmp");
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
    SDL_FRect dstrect = {
        player.position.x * 8 - 8 / 2,
        player.position.y * 8 - 8 / 2,
        8,
        8
    };
    SDL_RenderCopyExF(renderer, t, NULL, &dstrect, RAD_TO_DEG(player.angle), NULL, SDL_FLIP_NONE);
    SDL_FreeSurface(s);
    SDL_DestroyTexture(t);
}

void player_move(float dx, float dy) {
    float newX = player.position.x + dx;
    float newY = player.position.y + dy;

    int mapX = (int)newX;
    int mapY = (int)player.position.y;
    if (mapX >= 0 && mapX < WORLD_WIDTH && mapY >= 0 && mapY < WORLD_HEIGHT) {
        if (world[mapY * WORLD_WIDTH + mapX] == 0) {
            player.position.x = newX;
        }
    }

    mapX = (int)player.position.x;
    mapY = (int)newY;
    if (mapX >= 0 && mapX < WORLD_WIDTH && mapY >= 0 && mapY < WORLD_HEIGHT) {
        if (world[mapY * WORLD_WIDTH + mapX] == 0) {
            player.position.y = newY;
        }
    }
}

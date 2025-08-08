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

#include "ray.h"
#include "player.h"
#include "world.h"
#include "koronome.h"

ray_t castray(float angle) {
    SDL_FPoint p = player.position;

    SDL_FPoint d;
    d.x = SDL_cosf(angle);
    d.y = SDL_sinf(angle);

    int i = 0;
    while (1) {
        int mapX = (int)p.x;
        int mapY = (int)p.y;

        if (mapX < 0 || mapX >= WORLD_WIDTH || mapY < 0 || mapY >= WORLD_HEIGHT)
            break;

        if (world[mapY * WORLD_WIDTH + mapX] != 0)
            break;

        p.x += d.x * 0.01f;
        p.y += d.y * 0.01f;

        i++;
        if (i > 400) break;
    }

    ray_t ray;
    float dx = p.x - player.position.x;
    float dy = p.y - player.position.y;
    ray.distance = SDL_sqrtf(dx * dx + dy * dy); // primero se calcula
    ray.wallheight = SCREEN_HEIGHT / ray.distance;

    return ray;
}

void raycast(void) {
    int num_rays = SCREEN_WIDTH; // un rayo por pixel
    float sliceWidth = (float)SCREEN_WIDTH / (float)num_rays;
    float angleStep = player.fov / (float)num_rays;

    for (int i = 0; i < num_rays; i++) {
        float rayAngle = player.angle - (player.fov / 2.0f) + i * angleStep;
        ray_t ray = castray(rayAngle);

        // corrección de fisheye
        ray.distance *= SDL_cosf(rayAngle - player.angle);

        ray.wallheight = SCREEN_HEIGHT / ray.distance;
        if (ray.wallheight > SCREEN_HEIGHT) ray.wallheight = SCREEN_HEIGHT;

        draw_wall_slice(i, ray.wallheight, sliceWidth);
    }
}

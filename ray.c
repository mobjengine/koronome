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
    float rayDirX = SDL_cosf(angle);
    float rayDirY = SDL_sinf(angle);

    int mapX = (int)player.position.x;
    int mapY = (int)player.position.y;

    float sideDistX;
    float sideDistY;

    float deltaDistX = fabsf(1.0f / rayDirX);
    float deltaDistY = fabsf(1.0f / rayDirY);

    int stepX;
    int stepY;

    int hit = 0;
    int side = 0;

    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (player.position.x - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0f - player.position.x) * deltaDistX;
    }

    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (player.position.y - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0f - player.position.y) * deltaDistY;
    }

    while (hit == 0) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (mapX < 0 || mapX >= WORLD_WIDTH || mapY < 0 || mapY >= WORLD_HEIGHT)
            break;

        if (world[mapY * WORLD_WIDTH + mapX] != 0)
            hit = 1;
    }

    float perpWallDist;
    if (side == 0)
        perpWallDist = (mapX - player.position.x + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (mapY - player.position.y + (1 - stepY) / 2) / rayDirY;

    const float MIN_DISTANCE = 0.1f;
    if (perpWallDist < MIN_DISTANCE) perpWallDist = MIN_DISTANCE;

    float correctedDistance = perpWallDist * SDL_cosf(angle - player.angle);

    ray_t ray;
    ray.distance = correctedDistance;
    ray.wallheight = SCREEN_HEIGHT / correctedDistance;
    const float MAX_WALL_HEIGHT = SCREEN_HEIGHT;
    if (ray.wallheight > MAX_WALL_HEIGHT) ray.wallheight = MAX_WALL_HEIGHT;
    ray.side = side;
    ray.perpDist = perpWallDist;
    ray.stepX = stepX;
    ray.stepY = stepY;

    return ray;
}

void raycast(SDL_Surface *surface) {
    int num_rays = SCREEN_WIDTH;
    float sliceWidth = (float)SCREEN_WIDTH / (float)num_rays;
    float angleStep = player.fov / (float)num_rays;

    for (int i = 0; i < num_rays; i++) {
        float rayAngle = player.angle - (player.fov / 2.0f) + i * angleStep;
        ray_t ray = castray(rayAngle);

        float wallX;
        if (ray.side == 0)
            wallX = player.position.y + ray.perpDist * SDL_sinf(rayAngle);
        else
            wallX = player.position.x + ray.perpDist * SDL_cosf(rayAngle);

        wallX -= SDL_floorf(wallX);

        int texX = (int)(wallX * (float)surface->w);

        if (ray.side == 0 && ray.stepX > 0) texX = surface->w - texX - 1;
        if (ray.side == 1 && ray.stepY < 0) texX = surface->w - texX - 1;

        draw_wall_slice(i, ray.wallheight, sliceWidth, surface, texX);
    }
}

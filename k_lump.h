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

#pragma once

#include <SDL.h>
#include <zip.h>
#include "rxi_map.h"
#include "rxi_vec.h"

typedef struct {
    zip_uint64_t index;
    zip_uint64_t size;
    Uint8 zip;
} lump_t;

typedef map_t(lump_t) map_lump_t;

extern map_lump_t lumps;
extern vec_str_t zkds;

void K_LumpInit(int argc, const char **argv);
void K_LumpShutdown();
const lump_t* K_LumpGet(const char *key);
void K_LumpData(const lump_t *lump, void *buffer);

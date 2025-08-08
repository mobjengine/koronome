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

#pragma once

#include <SDL.h>
#include <zip.h>
#include "rxi/vec.h"
#include "rxi/map.h"

typedef struct {
    zip_uint64_t index;
    zip_uint64_t size;
    Uint8 zip;
} lump_t;

typedef map_t(lump_t) map_lump_t;

extern vec_str_t zips;
extern map_lump_t lumps;

void lump_init();
void lump_shutdown();
lump_t* lump_get(const char *name);
void lump_data(lump_t *lump, void *buffer);

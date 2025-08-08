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

#pragma once

#include <SDL.h>
#include "vec.h"
#include "map.h"

typedef struct {
    Sint8   identification;
    Sint32  numlumps;
    Sint32  infotableofs;
} wadinfo_t;

typedef struct {
    Sint32  filepos;
    Sint32  size;
    Sint8   name[8];
} filelump_t;

typedef struct {
    Sint32  filepos;
    Sint32  size;
    Uint8   wad;
} lump_t;

typedef map_t(lump_t) map_lump_t;

extern vec_str_t wads;
extern map_lump_t lumps;

void wad_init();
void wad_shutdown();
lump_t* wad_get(const char *name);
void wad_data(lump_t *lump, void *buffer);

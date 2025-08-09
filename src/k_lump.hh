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

#include <zip.h>
#include <vector>
#include <map>
#include <string>

typedef struct {
    zip_uint64_t index;
    zip_uint64_t size;
    uint8_t zip;

    void data(void *buffer);
} lump_t;

extern std::vector<std::string> zips;
extern std::map<std::string, lump_t> lumps;

void K_LumpInit(int argc, const char **argv);

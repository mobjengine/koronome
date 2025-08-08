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

#include "wad.h"

vec_str_t wads;
map_lump_t lumps;

void wad_init() {
    vec_init(&wads);
    map_init(&lumps);

    vec_push(&wads, "koronome.wad");

    int wad_i;
    const char *wad_s;
    vec_foreach(&wads, wad_s, wad_i) {
        FILE *fp = fopen(wad_s, "rb");

        wadinfo_t wadinfo;
        fread(&wadinfo, sizeof(wadinfo_t), 1, fp);

        fseek(fp, wadinfo.infotableofs, SEEK_SET);
        for(int i = 0;i < wadinfo.numlumps;i++) {
            filelump_t filelump;
            fread(&filelump, sizeof(filelump_t), 1, fp);

            lump_t lump = {
                filelump.filepos,
                filelump.size,
                wad_i
            };

            char name[9];
            memset(name, 0, 9);
            memcpy(name, filelump.name, 8);

            map_set(&lumps, name, lump);
        }

        fclose(fp);

        SDL_Log("Adding %s (%d lumps)", wad_s, wadinfo.numlumps);
    }
}

void wad_shutdown() {
    vec_deinit(&wads);
    map_deinit(&lumps);
}

lump_t* wad_get(const char *name) {
    return map_get(&lumps, name);
}

void wad_data(lump_t *lump, void *buffer) {
    FILE *fp = fopen(wads.data[lump->wad], "rb");
    fseek(fp, lump->filepos, SEEK_SET);
    fread(buffer, 1, lump->size, fp);
    fclose(fp);
}

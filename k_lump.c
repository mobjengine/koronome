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

#include "k_lump.h"
#include "k_main.h"

map_lump_t lumps;
vec_str_t zkds;

void K_LumpInit(int argc, const char **argv) {
    map_init(&lumps);
    vec_init(&zkds);

    vec_push(&zkds, "koronome.zkd");

    for(int i = 0;i < argc;i++) {
        if(CSTR_ENDS_WITH(argv[i], ".zkd")) {
            vec_push(&zkds, argv[i]);
        }
    }

    int zkd_i;
    const char *zkd_s;
    vec_foreach(&zkds, zkd_s, zkd_i) {
        zip_t *z = zip_open(zkd_s, ZIP_RDONLY, NULL);
        zip_uint64_t ze = zip_get_num_entries(z, 0);
        Uint64 total = 0;

        while(ze--) {
            zip_stat_t zt;
            zip_stat_index(z, ze, 0, &zt);

            if(CSTR_ENDS_WITH(zt.name, "/")) continue;

            lump_t lump = {zt.index, zt.size, zkd_i};
            map_set(&lumps, zt.name, lump);

            total++;
        }

        zip_close(z);

        SDL_Log("Adding %s (%ld lumps)", zkd_s, total);
    }
}

void K_LumpShutdown() {
    map_deinit(&lumps);
    vec_deinit(&zkds);
}

const lump_t* K_LumpGet(const char *key) {
    return map_get(&lumps, key);
}

void K_LumpData(const lump_t *lump, void *buffer) {
    zip_t *z = zip_open(zkds.data[lump->zip], ZIP_RDONLY, NULL);
    zip_file_t *zf = zip_fopen_index(z, lump->index, 0);

    zip_fread(zf, buffer, lump->size);

    zip_fclose(zf);
    zip_close(z);
}

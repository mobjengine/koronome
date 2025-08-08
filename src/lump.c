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

#include "lump.h"
#include "koronome.h"

vec_str_t zips;
map_lump_t lumps;

void lump_init(int argc, const char **argv) {
    SDL_Log("Init lumps");

    vec_init(&zips);
    map_init(&lumps);

    vec_push(&zips, "koronome.pk3");

    for(int i = 0;i < argc;i++) {
        if(CSTR_ENDS_WITH(argv[i], ".pk3")) {
            vec_push(&zips, argv[i]);
        }
    }

    int zip_i;
    const char *zip_s;
    vec_foreach(&zips, zip_s, zip_i) {
        zip_t *z = zip_open(zip_s, ZIP_RDONLY, NULL);
        zip_uint64_t ze = zip_get_num_entries(z, 0);
        zip_uint64_t total = 0;

        for(zip_uint64_t i = 0;i < ze;i++) {
            zip_stat_t st;
            zip_stat_index(z, i, 0, &st);
            if(CSTR_ENDS_WITH(st.name, "/")) continue;
            map_set(&lumps, st.name, ((lump_t){st.index, st.size, zip_i}));
            total++;
        }

        zip_close(z);

        SDL_Log("Adding %s (%ld lumps)", zip_s, total);
    }
}

void lump_shutdown() {
    SDL_Log("Shutdown lumps");
    vec_deinit(&zips);
    map_deinit(&lumps);
}

lump_t* lump_get(const char *name) {
    return map_get(&lumps, name);
}

void lump_data(lump_t *lump, void *buffer) {
    zip_t *z = zip_open(zips.data[lump->zip], ZIP_RDONLY, NULL);
    zip_file_t *zf = zip_fopen_index(z, lump->index, 0);
    zip_fread(zf, buffer, lump->size);
    zip_fclose(zf);
    zip_close(z);
}

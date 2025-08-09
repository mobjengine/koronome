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

#include "k_lump.hh"
#include "k_main.hh"

std::vector<std::string> zips;
std::map<std::string, lump_t> lumps;

void K_LumpInit(int argc, const char **argv) {
    zips.push_back("koronome.pk3");

    for(int i = 0;i < argc;i++) {
        if(CSTR_ENDS_WITH(argv[i], ".pk3")) {
            zips.push_back(argv[i]);
        }
    }

    uint8_t zip_i = 0;
    for(std::string zip : zips) {
        zip_t *z = zip_open(zip.c_str(), ZIP_RDONLY, NULL);
        zip_uint64_t ze = zip_get_num_entries(z, 0);
        zip_uint64_t total = 0;

        for(zip_uint64_t i = 0;i < ze;i++) {
            zip_stat_t st;
            zip_stat_index(z, i, 0, &st);
            if(CSTR_ENDS_WITH(st.name, "/")) continue;
            lumps[st.name] = (lump_t){st.index, st.size, zip_i};
            total++;
        }

        zip_close(z);
        zip_i++;
    }
}

void lump_t::data(void *buffer) {
    zip_t *z = zip_open(zips[zip].c_str(), ZIP_RDONLY, NULL);
    zip_file_t *zf = zip_fopen_index(z, index, 0);
    zip_fread(zf, buffer, size);
    zip_fclose(zf);
    zip_close(z);
}

/* glitchme.c:  introduce random noise in a stream
 * Copyright (C) 2015 Mike Bionchik

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: glitchme <rand factor> <seed (optional int)>\n");
        return 1;
    } else {
        double fl = atof(argv[1]);
        unsigned int rf = round((fl<0.0?0.0:(fl>1.0?1.0:fl))*UINT_MAX), r, cnt=0;
        int nr, nw, ch;
        int seed;
        if (argc == 3) {
            seed = atoi(argv[2]);
        } else {
            seed = time(NULL);
        }
        srand((unsigned int)seed);
        nr = fread(&ch, sizeof(int), 1, stdin);
        while (nr != 0) {
            r = (unsigned int)rand();
            if (r <= rf) {
                ch ^= rand();
                nw = fwrite(&ch, sizeof(int), 1, stdout);
                cnt++;
            } else {
                nw = fwrite(&ch, sizeof(int), 1, stdout);
            }
            nr = fread(&ch, sizeof(int), 1, stdin);
        }
        return 0;
    }
}

#include <stdlib.h>
#include <stdio.h>
#include "shl/nuklear.h"
#include "shl/stb_ds.h"

int main(int argc, char *argv[]) {
    const int count = 5;
    struct nk_color *colors = NULL;
    int i;

    for (i = 0; i < count; ++i) {
        stbds_arrput(colors, nk_rgb((i * 255 / (count-1)), 255, 255));
    }
    for (i = 0; i < stbds_arrlen(colors); ++i) {
        printf("[%d] { %d, %d, %d }\n", i, colors[i].r, colors[i].g, colors[i].b);
    }

    stbds_arrfree(colors);
    return EXIT_SUCCESS;
}

#ifndef SHL_STB_H
#define SHL_STB_H

#include <string.h>
#include <stdlib.h>

#define STBDS_NO_SHORT_NAMES
#include <stb_ds.h>

/* strarr_put() works like stbds_arrput() but duplicates the new item value
 * with strdup(). The array must be freed with strarr_free() to deallocate
 * each item memory, and replacement of array items is not possible without
 * more work (not needed for now)
 */
#define strarr_put(a, v)    (stbds_arrput(a, strdup(v)))
#define strarr_free(a)      do{for(int i=0;i<stbds_arrlen(a);++i)free(a[i]);a=stbds_arrfree(a);} while(0)

#endif /* SHL_STB_H */

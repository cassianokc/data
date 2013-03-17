#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "hmap.h"


#define HASH_SIZE 30001


unsigned long hash(const void *a)
{
    return *((unsigned long *)a)%HASH_SIZE;
}


void utest_hmap(void)
{
    struct hmap *map;
    unsigned long i=0, j=0;
    map = hmap_init(HASH_SIZE, sizeof(unsigned long), sizeof(unsigned long), hash);
    while (hmap_insert(map, &i, &j) == SUCCESS)
    {
        i++;
        j++;
    }
    do
    {
        i = i-2;
        j = j-2;
    } while (hmap_remove(map, &i, &j) == SUCCESS);
    i = 20;
    j = 20;
    hmap_insert(map, &i, &j);
    hmap_print(map);
    hmap_free(map);
    return;
}


int main(void)
{
#ifdef UTEST_HMAP
		utest_hmap();
#endif
    return 0;
}

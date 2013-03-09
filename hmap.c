#include "hmap.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_empty(void *data, unsigned long size)
{
	register unsigned long i;
	for (i=0; i<size; i++)
	{
		if (((unsigned char *) data)[i] != 0x00)
			return FALSE;
	}
	return TRUE;
}

bool is_deleted(void *data, unsigned long size)
{
	register unsigned long i;
	for (i=0; i<size; i++)
	{
		if (((unsigned char *) data)[i] != 0xff)
			return FALSE;
	}
	return TRUE;
}

bool is_reserved(void *data, unsigned long size)
{
	register unsigned long i;
	if (((unsigned char *) data)[0] != 0x00 && ((unsigned char *) data)[0] != 0xff)
		return FALSE;
	for (i=0; i<size; i++)
	{
		if (((unsigned char *) data)[i] != ((unsigned char *) data)[0])
			return FALSE;
	}
	return TRUE;
}

struct hmap *hmap_init(unsigned long map_size, unsigned long data_size,
		unsigned long key_size, unsigned long (*hash)(const void *))
{
	struct hmap *map;
	map = malloc(sizeof(struct hmap));
	if (map == NULL)
		return NULL;
	map->map = malloc(map_size*(key_size+data_size));
	if (map->map == NULL)
	{
		free(map);
		return NULL;
	}
    memset(map->map, 0x00, map_size*(key_size+data_size));
	map->map_size = map_size;
	map->key_size = key_size;
	map->data_size = data_size;
	map->hash = hash;
	return map;
}

void hmap_free(struct hmap *map)
{
	free(map->map);
	free(map);
}

int hmap_insert(struct hmap *map, void *key, void *data)
{
	unsigned long i=0, index=map->hash(key);
	unsigned char *aux = map->map;
	while (!is_reserved(aux+((index+i)%map->map_size)*(map->key_size+map->data_size),
				map->key_size + map->data_size))
		/*While haven't found a empty or deleted space*/
	{
		if (i==map->map_size) /*If already passed through the whole map*/
			return FAILURE;
		i++;
	}
	memcpy(aux+((index+i)%map->map_size)*(map->key_size+map->data_size), key,
			map->key_size); /*Write key and data*/
	memcpy(aux+((index+i)%map->map_size)*(map->key_size+map->data_size)+map->key_size,
			data, map->data_size);
	return SUCCESS;
}

int hmap_remove(struct hmap *map, void *key, void *data)
{
	unsigned long i=0, index=map->hash(key);
	unsigned char *aux = map->map;
	while (!is_empty(aux+((index+i)%map->map_size)*(map->key_size+map->data_size),
				map->key_size+map->data_size)&&i!=map->map_size)
	{
		if (memcmp(aux+((index+i)%map->map_size)*(map->key_size+map->data_size), key,
					map->key_size) == 0)/*If found key, copy to data and set mem to deleted*/
		{
			memcpy(data, aux+((index+i)%map->map_size)*(map->key_size+map->data_size)+
					map->key_size, map->data_size);
			memset(aux+((index+i)%map->map_size)*(map->key_size+map->data_size), 0xff,
					map->key_size+map->data_size);
			return SUCCESS;
		}
		i++;
	}
	return FAILURE;
}

int hmap_search(struct hmap *map, void *key, void *data)
{
	unsigned long i=0, index=map->hash(key);
	unsigned char *aux = map->map;
	while (!is_empty(aux+((index+i)%map->map_size)*(map->key_size+map->data_size),
				map->key_size+map->data_size)&&i!=map->map_size)
	{
		if (memcmp(aux+((index+i)%map->map_size)*(map->key_size+map->data_size), key,
					map->key_size) == 0)/*If found key, copy to data*/
		{
			memcpy(data, aux+((index+i)%map->map_size)*(map->key_size+map->data_size)+
					map->key_size, map->data_size);
			return SUCCESS;
		}
		i++;
	}
	return FAILURE;
}

void hmap_print(struct hmap *map)
{
	unsigned long i, j;
	unsigned char *aux = map->map;
    printf("Struct hmap at %p\n", (void *) map);
    printf("map_size=%lu    key_size=%lu    data_size=%lu\n", map->map_size,
        map->key_size, map->data_size);
	for (i=0; i<map->map_size; i++)
	{
        if (is_empty(aux+i*(map->key_size+map->data_size),
					map->key_size+map->data_size))
			printf("Block %lu: empty\n", i);
		else if (is_deleted(aux+i*(map->key_size+map->data_size),
					map->key_size+map->data_size))
			printf("Block %lu: deleted\n", i);
		else
		{
			printf("Block %lu: key = ", i);
			for (j=0; j<map->key_size; j++)
				printf("%u ", aux[i*(map->key_size+map->data_size)+j]);
			printf("data = ");
			for (j=0; j<map->key_size; j++)
				printf("%u ", aux[i*(map->key_size+map->data_size)+map->key_size+j]);
			printf("\n");
		}
	}
}

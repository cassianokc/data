#ifndef HMAP_H
#define HMAP_H

#include "common.h"

/*
*		@section Description A generic hash map data structure implementation, using a
* probing collision solving. The hash map stores elements with elem_size bytes 
* each identified by a key with key_size bytes and can store up to 
* map_size/(elem_size+key_size).
* 	There is a reserved key/elem combination that is used to mark empty/deleted
* map positions. The reserved key/elem consist in all the bits in the elem and the
* key been only 1s or only 0s.
* 	Each element is written on the map, preceded by its key.
*/
struct hmap
{
	unsigned long map_size;
	unsigned long elem_size;
	unsigned long key_size;	
	void *map;
	unsigned long (*hash)(void *);
};



bool is_empty(void *, unsigned long);
bool is_deleted(void *, unsigned long);
/*
* 	Inits the a hash map structure and returns a pointer to it.
* 	@param map_size Size of the hash map.
* 	@param elem_size Size of the elements that will be stored in the map.
* 	@param key_size Size of the key that will be used to identify each element.
* 	@param hash Pointer to a function that calculates a key hash.
* 	@return Returns a pointer to the created hmap structure. If there isn't enough 
* memory, returns a NULL pointer. 
*/

struct hmap *hmap_init(unsigned long map_size, unsigned long key_size, 
	unsigned long elem_size, unsigned long (*hash)(void *)); 
/*
*		Frees all memory used by the hmap structure.
* 	@param map hmap structure that will be freed.
*/

void hmap_free(struct hmap *map);
/*
* 	Inserts a new element identified by a key on a given hmap structure.
*		@param map Pointer to a hmap structure where elem is going to be added.
* 	@param key Pointer to the key which identifies the element.
* 	@param elem Pointer to the element that will be added on hmap.
* 	@return Return SUCCESS if the insertion was successfull, if there wasn't space 
* on the map returns FAILURE.
*/

int hmap_insert(struct hmap *map, void *key, void *elem);
/*
* 	Removes a element identified by key on a given hmap strucuture.
* 	@param map Pointer to a hmap structure from where the elem is going to be 
* removed.
* 	@param key Pointer to a key that identifies the element to be removed 
* 	@param elem Pointer to which the removed element will be writen before removal.
* 	@return Returns SUCCESS if the element was found and the removal was successfull
* and FAILURE otherwise.
*/

int hmap_remove(struct hmap *map, void *key, void *elem);
/*
* 	Searches a element identified by key on a given hmap strucuture.
* 	@param map Pointer to a hmap structure from where the element is going to be 
* searched.
* 	@param key Pointer to a key that identifies the element to be searched. 
* 	@param elem Pointer to which the element data will be writen.
* 	@return Returns SUCCESS if the element was found  and FAILURE otherwise.
*/
int hmap_search(struct hmap *map, void *key, void *elem);

/*
*		Prints all data in the hmap structure for debugging.
* 	@param map Pointer to the hmap structure that will be printed.
*/
void hmap_print(struct hmap *map);


#endif

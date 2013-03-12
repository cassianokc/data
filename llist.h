#ifndef LLIST_H
#define LLIST_H


struct llist_node
{
	struct llist_node *next;
	void * key;
	void * data; };

struct llist
{
	struct llist_node sentinel;
	unsigned long data_size;
	unsigned long key_size;
	int (*compare)(const void *, const void *);
};

/*
* 	Allocates a llist struct and returns a pointer to it.
* 	@param key_size Number of bytes on the key that will identify the data on 
* the struct.
* 	@param data_size Number of bytes in each data block.
*	@param compare Pointer to a function that returns 0 if two keys are equal,
* a value greater then zero if the key pointed by the first pointer is greater 
* then the second and lesser then zero otherwise.
*	@return Returns a pointer to the allocated llist struct, if there isn't
* space enough returns a NULL pointer.
*/
struct llist *llist_init(unsigned long key_size, unsigned long data_size,
		int (*compare)(const void *, const void *));

/*
*	Frees all memory used by a llist struct.
* 	@param list Pointer to the struct that will be freed.
*/
void llist_free(struct llist *list);

int llist_append(struct llist *list, void *key, void *data);
int llist_insert(struct llist *list, void *key, void *data);
int llist_remove(struct llist *list, void *key, void *data);
int llist_search(struct llist *list, void *key, void *data);

/*
*       Prints all data in the llist structure for debugging.
*       @param map Pointer to the llist structure that will be printed.
*/
void llist_print(struct llist *list);
struct llist_node *llist_node_alloc(struct llist *list, void *key, void *data);
void llist_node_free(struct llist_node *node);
#endif

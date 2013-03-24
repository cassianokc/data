#ifndef LLIST_H
#define LLIST_H

/*
*		@section Description A generic circular linked list implementation, 
* using sentinel node. The user pass a pointer to a compare function that
* compares each key. The linked list can be extend until there is no memory
* left.
*/
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

struct llist_node *llist_node_alloc(struct llist *list, void *key, void *data);
void llist_node_free(struct llist_node *node);


/*
* 	Allocates a llist struct and returns a pointer to it.
* 	@param key_size Number of bytes on the key that will identify the data on 
* the struct.
* 	@param data_size Number of bytes in each data block.
*	@param compare Pointer to a function that returns 0 if two keys are equal
* , a value greater then zero if the key pointed by the first pointer is 
* greater then the second and lesser then zero otherwise.
*		@return Returns a pointer to the allocated llist struct, if there isn't
* space enough returns a NULL pointer.
*/
struct llist *llist_init(unsigned long key_size, unsigned long data_size,
		int (*compare)(const void *, const void *));

/*
*		Frees all memory used by a llist struct.
* 	@param list Pointer to the struct that will be freed.
*/
void llist_free(struct llist *list);

/*
* 	Allocates a new node and appends it on the beggining of the linked 
* list.
* 	@param list Pointer to the llist struct in which the new node will bei
* appended.
* 	@param key Pointer to the key that identifies the data block.
* 	@param data Pointer to the data block that will be stored on the list.
* 	@return Returns SUCCESS if the procedure was successfull and if there 
* isn't space for the new node returns FAILURE.
*/
int llist_append(struct llist *list, void *key, void *data);

/*
* 	Allocates a new node and inserts it on after the first block that has
* a lesser key.
* 	If you use only llist_insert instead of llist_append, you the list will
* always be ordered.
* 	@param list Pointer to the llist struct in which the new node will be
* inserted.
* 	@param key Pointer to the key that identifies the data block.
* 	@param data Pointer to the data block that will be stored on the list.
* 	@return Returns SUCCESS if the procedure was successfull and if there 
* isn't space for the new node returns FAILURE.
*/
int llist_insert(struct llist *list, void *key, void *data);

/*
*		Searches for a node with key equal to the key pointer, if found one, 
* removes it from the list and copy the node data to data pointer.
*		@param list Pointer to the llist struct from which the node will be
* removed.
*		@param key Pointer to the key that identifies the data block that will
* be removed.
* 	@param data Pointer to which the data block found will be written to.
* 	@param return Returns SUCCESS if a block containing key was found and 
* successfully removed, returns FAILURE otherwise.
*/ 
int llist_remove(struct llist *list, void *key, void *data);

/*
*		Searches for a node with key equal to the key pointer, if one is found
* its data contents are written to the data pointer.
* 	@param list Pointer to the llist struct to be searched.
* 	@param key Pointer to the key that will be searched.
*		@param data Pointer to the data block that will be written.
* 	@param return Returns SUCCESS if a block containing key was found and
* returns FAILURE otherwise. 
*/ 
int llist_search(struct llist *list, void *key, void *data);

/*
* 	Prints all data in the llist structure for debugging.
*   @param map Pointer to the llist structure that will be printed.
*/
void llist_print(struct llist *list);


#endif

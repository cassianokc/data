#ifndef SSTACK_H
#define SSTACK_H

#include "common.h"

/*
* 	@section Description A generic static stack data structure 
* implementation, the stack can store size elements of size elem_size each.
* 	The elements on the stack are stored in a array pointed by data, and
* can be acessed via the sstack_insert and sstack_remove functions.
*/
struct sstack
{
	unsigned long size;
	unsigned long end;
	unsigned long elem_size;
	void *data;
};

/*
* 	Inits a sstack structure and returns a pointer to it.
* 	@param size Number of blocks, or elems on the stack.
* 	@param elem_size Size of each block.
*		@return Returns a pointer to the new sstack structure, if there isn't
* space returns a NULL pointer.
*/

struct sstack *sstack_init(unsigned long size, unsigned long elem_size);
/*
* 	Frees all memory consumed by a sstack structure.
* 	@param stack Pointer to the stack that will be freed.
*/
void sstack_free(struct sstack *stack);

/*
* 	Tests whether a sstack structure contains any elements.
* 	@param stack Pointer to the stack that will be tested.
* 	@return Returns TRUE if the stack is empty, FALSE otherwise.
*/
bool sstack_is_empty(struct sstack *stack);

/*
* 	Tests whether a sstack structure is full.
* 	@param stack Pointer to the stack that will be tested.
* 	@return Returns TRUE if the stack is full, FALSE otherwise.
*/
bool sstack_is_full(struct sstack *stack);

/*
* 	Pops a element from the top of the stack. 
*		@param stack Pointer to the stack from which the elem will be popped.
* 	@param elem	A pointer to where the popped element will be written to.
* 	@return Returns SUCCESS if the stack isn't empty and the operation was
* successfull, FAILURE otherwise.
*/
int sstack_remove(struct sstack *stack, void *elem);

/*
* 	Pushes a element in the top of the stack. 
*		@param stack Pointer to the stack to which the elem will be pushed.
* 	@param elem	A pointer to the element that will be written to.
* 	@return Returns SUCCESS if the stack isn't full and the operation was
* successfull, FAILURE otherwise.
*/
int sstack_insert(struct sstack *stack, void *elem);

/*
* 	Prints data in the sstack structure.
* 	@param stack POinter to the sstack structure that will be printed.
*/
void sstack_pritn(struct sstack *stack);


#endif

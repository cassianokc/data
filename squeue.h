#ifndef SQUEUE_H
#define SQUEUE_H

/*
* 	@section Description A static queue implementation as a circular buffer
* using being/end pointer with a element counter inside, the elements are
* acessed via squeue_insert and squeue_remove functions.
* 	The queue can store up to size elements, with elem_size bytes each.
*/
struct squeue
{
	unsigned long size;
	unsigned long begin;
	unsigned long end;
	unsigned long count;
	unsigned long elem_size;
	void *data;
};

/*
* 	Inits a new squeue data structure with size elements with elem_size
* each.
*		@param size Number of elements in the queue.
* 	@param elem_size Size of each element in the queue.
* 	@return Returns a pointer to a initialized squeue structure, if there
* isn't space returns a NULL pointer.
*/
struct squeue *squeue_init(unsigned long size, unsigned long elem_size);

/*
* 	Frees all memory used by the squeue structure.
* 	@param queue Pointer to the squeue structure that will be freed.
*/
void squeue_free(struct squeue *queue);

/*
* 	Tests whether a squeue structure contains any elements.
* 	@param queue Pointer to the queue that will be tested.
* 	@return Returns TRUE if the queue is empty, FALSE otherwise.
*/
bool squeue_is_empty(struct squeue *queue);

/*
* 	Tests whether a squeue structure is full.
* 	@param queue Pointer to the queue that will be tested.
* 	@return Returns TRUE if the queue is full, FALSE otherwise.
*/
bool squeue_is_full(struct squeue *queue);

/*
* 	Pops a element from the top of the queue. 
*		@param queue Pointer to the queue from which the elem will be popped.
* 	@param elem	A pointer to where the popped element will be written to.
* 	@return Returns SUCCESS if the queue isn't empty and the operation was
* successfull, FAILURE otherwise.
*/
int squeue_remove(struct squeue *queue, void *elem);

/*
* 	Pushes a element in the top of the queue. 
*		@param queue Pointer to the queue to which the elem will be pushed.
* 	@param elem	A pointer to the element that will be written to.
* 	@return Returns SUCCESS if the queue isn't full and the operation was
* successfull, FAILURE otherwise.
*/
int squeue_insert(struct squeue *queue, void *elem);

/*
* 	Prints data in the squeue structure.
* 	@param queue Pointer to the squeue structure that will be printed.
*/
void squeue_print(struct squeue *queue);



#endif

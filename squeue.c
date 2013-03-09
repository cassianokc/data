#include "common.h"
#include "squeue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct squeue *squeue_init(unsigned long size, unsigned long elem_size)
{
	struct squeue *queue;
	queue = malloc(sizeof(struct squeue));
	if (queue == NULL)
		return NULL;
	queue->size = size;
	queue->begin = 0;
	queue->end = 0;
	queue->count = 0;
	queue->elem_size = elem_size;
	queue->data = malloc(size*elem_size);
	return queue;
}

void squeue_free(struct squeue *queue)
{
	free(queue->data);
	free(queue);
}

bool squeue_is_empty(struct squeue *queue)
{
	return (queue->count == 0);
}

bool squeue_is_full(struct squeue *queue)
{
	return (queue->count == queue->size);
}

int squeue_remove(struct squeue *queue, void *elem)
{
	unsigned char *aux=queue->data;
	if (squeue_is_empty(queue))
		return FAILURE;
	memcpy(elem, aux+queue->begin*queue->elem_size, queue->elem_size);
	queue->begin = (queue->begin+1)%queue->size;
	queue->count--;
	return SUCCESS;
}

int squeue_insert(struct squeue *queue, void *elem)
{
	unsigned char *aux=queue->data;
	if (squeue_is_full(queue))
		return FAILURE;
	memcpy(aux+queue->end*queue->elem_size, elem, queue->elem_size);
	queue->end = (queue->end+1)%queue->size;
	queue->count++;
	return SUCCESS;
}

void squeue_print(struct squeue *queue)
{
	unsigned long i, j;
	unsigned char *aux=queue->data;
	printf("Struct squeue at %p\n", (void *) queue);
	printf("size=%lu	begin=%lu	end=%lu	elem_size=%lu\n", queue->size,
		queue->begin, queue->end, queue->elem_size);
	for (i=0; i<queue->count; i++)
	{
		printf("Block %lu: ", ((queue->begin+i)%queue->size));
		for (j=0; j<queue->elem_size; j++)
		{
			printf("%u ", aux[((queue->begin+i)%queue->size)*queue->elem_size+j]);
		}
		printf("\n");
	}
}

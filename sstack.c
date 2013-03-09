#include "common.h"
#include "sstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct sstack *sstack_init(unsigned long size, unsigned long elem_size)
{
	struct sstack *stack;
	stack = malloc(sizeof(struct sstack));
	if (stack == NULL)
		return NULL;
	stack->size = size;
	stack->end = 0;
	stack->elem_size = elem_size;
	stack->data = malloc(size*elem_size);
	return stack;
}

void sstack_free(struct sstack *stack)
{
	free(stack->data);
	free(stack);
}

bool sstack_is_empty(struct sstack *stack)
{
	return (stack->end == 0);
}

bool sstack_is_full(struct sstack *stack)
{
	return (stack->size == stack->end);
}

int sstack_remove(struct sstack *stack, void *elem)
{
	unsigned char *aux=stack->data;
	if (sstack_is_empty(stack))
		return FAILURE;
	stack->end--;
	memcpy(elem, aux+stack->end*stack->elem_size, stack->elem_size);
	return SUCCESS;
}

int sstack_insert(struct sstack *stack, void *elem)
{
	unsigned char *aux=stack->data;
	if (sstack_is_full(stack))
		return FAILURE;
	memcpy(aux+stack->end*stack->elem_size, elem, stack->elem_size);
	stack->end++;
	return SUCCESS;
}

void sstack_print(struct sstack *stack)
{
	unsigned long i, j;
	unsigned char *aux=stack->data;
	printf("Struct sstack at %p\n", (void *) stack);
	printf("size=%lu	end=%lu		elem_size=%lu\n", stack->size, stack->end, 
		stack->elem_size);
	for (i=0; i<stack->end; i++)
	{
		printf("Block %lu: ", i);
		for (j=0; j<stack->elem_size; j++)
		{
			printf("%u ", aux[i*stack->elem_size+j]);
		}		
		printf("\n");
	} 	
}


#include "common.h"
#include "sstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct sstack *sstack_init(unsigned long size, unsigned long data_size)
{
	struct sstack *stack;
	stack = malloc(sizeof(struct sstack));
	if (stack == NULL)
		return NULL;
	stack->size = size;
	stack->end = 0;
	stack->data_size = data_size;
	stack->data = malloc(size*data_size);
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

int sstack_remove(struct sstack *stack, void *data)
{
	unsigned char *aux=stack->data;
	if (sstack_is_empty(stack))
		return FAILURE;
	stack->end--;
	memcpy(data, aux+stack->end*stack->data_size, stack->data_size);
	return SUCCESS;
}

int sstack_insert(struct sstack *stack, void *data)
{
	unsigned char *aux=stack->data;
	if (sstack_is_full(stack))
		return FAILURE;
	memcpy(aux+stack->end*stack->data_size, data, stack->data_size);
	stack->end++;
	return SUCCESS;
}

void sstack_print(struct sstack *stack)
{
	unsigned long i, j;
	unsigned char *aux=stack->data;
	printf("Struct sstack at %p\n", (void *) stack);
	printf("size=%lu	end=%lu		data_size=%lu\n", stack->size, stack->end, 
		stack->data_size);
	for (i=0; i<stack->end; i++)
	{
		printf("Block %lu: ", i);
		for (j=0; j<stack->data_size; j++)
		{
			printf("%u ", aux[i*stack->data_size+j]);
		}		
		printf("\n");
	} 	
}


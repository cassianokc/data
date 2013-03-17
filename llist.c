#include "llist.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct llist *llist_init(unsigned long key_size, unsigned long data_size,
		int (*compare)(const void *, const void *))
{
	struct llist *list;
	list = malloc(sizeof(struct llist));
	if (list == NULL)
		return NULL;
	list->sentinel.next = &list->sentinel;
	list->key_size = key_size;
	list->data_size = data_size;
	list->compare = compare;
	return list;
}

void llist_free(struct llist *list)
{
	struct llist_node *i, *j;
	i = list->sentinel.next;
	while (i!=&list->sentinel)
	{
		j = i;
		i = i->next;
		free(j->key);
		free(j->data);
		free(j);
	}
	free(list);
}

int llist_append(struct llist *list, void *key, void *data)
{
	struct llist_node *new_node;
	if ((new_node = llist_node_alloc(list, key, data)) == NULL)
		return FAILURE;
	new_node->next = list->sentinel.next;
	list->sentinel.next = new_node;
	return SUCCESS;
}

int llist_insert(struct llist *list, void *key, void *data)
{
	struct llist_node *new_node, *i;
	if ((new_node = llist_node_alloc(list, key, data)) == NULL)
		return FAILURE;
	i = &list->sentinel;
	while (i->next != &list->sentinel)
	{
		if (list->compare(i->next->key, key) == 0)
			/* If key match found, just write the new data and returns. */
		{
			llist_node_free(new_node);
			memcpy(i->next->data, data, list->data_size);
			return SUCCESS;
		}
		if (list->compare(i->next->key, key) < 0)
		{
			new_node->next = i->next;
			i->next = new_node;
			return SUCCESS;
		}
		i = i->next;
	}
	new_node->next = i->next;
	i->next = new_node;
	return SUCCESS;
}

int llist_remove(struct llist *list, void *key, void *data)
{
	struct llist_node *i, *j;
	i = &list->sentinel;
	while (i->next != &list->sentinel)
	{
		prefetch(i->next->next->next);
		if (list->compare(i->next->key, key) == 0)
		{
			j = i->next;
			i->next = j->next;
			memcpy(data, j->data, list->data_size);
			llist_node_free(j);
			return SUCCESS;
		}
		i = i->next;
	}
	return FAILURE;
}

int llist_search(struct llist *list, void *key, void *data)
{
	struct llist_node *i;
	i = list->sentinel.next;
	while (i != &list->sentinel)
	{
		prefetch(i->next->next->next);
		if (list->compare(i->key, key) == 0)
		{
			memcpy(data, i->data, list->data_size);
			return SUCCESS;
		}
	}
	return FAILURE;
}

void llist_print(struct llist *list)
{
	struct llist_node *i;
	unsigned long j;
	unsigned char *aux;
	i = list->sentinel.next;
	printf("Struct llist at %p\n", (void *) list);
	printf("key_size=%lu  data_size=%lu\n", list->key_size, list->data_size);
	while (i!=&list->sentinel)
	{
		aux = i->key;
		printf("Key: ");
		for (j=0; j<list->key_size; j++)
			printf("%u ", aux[j]);
		aux = i->data;
		printf("\nData: ");
		for (j=0; j<list->data_size; j++)
			printf("%u ", aux[j]);
		printf("\n");
		i = i->next;
	}
}

struct llist_node *llist_node_alloc(struct llist *list, void *key, void *data)
{
	struct llist_node *new_node;
	new_node = malloc(sizeof(struct llist_node));
	if (new_node == NULL)
		return NULL;
	new_node->key = malloc(list->key_size);
	if (new_node->key == NULL)
	{
		free(new_node);
		return NULL;
	}
	new_node->data = malloc(list->data_size);
	if (new_node->data == NULL)
	{
		free(new_node->key);
		free(new_node);
		return NULL;
	}
	memcpy(new_node->key, key, list->key_size);
	memcpy(new_node->data, data, list->data_size);
	return new_node;
}

void llist_node_free(struct llist_node *node)
{
	free(node->key);
	free(node->data);
	free(node);
}

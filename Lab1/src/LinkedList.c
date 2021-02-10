#include "LinkedList.h"
#include "Common.h"
#include <stdlib.h>

bool list_is_empty(LinkedList * list)
{
	return (list->head == NULL);
}

bool list_insert(LinkedList *list, ListElement * node)
{
	if (list == NULL || node == NULL)
		return false;

	node->next = list->head;
	if (list->head != NULL)
		list->head->prev = node;

	list->head = node;
	node->prev = NULL;

	return true;
}

ListElement * list_search(LinkedList * list, ListElement * node)
{
	ListElement *temp;

	for (temp = list->head; temp; temp = temp->next)
		if (node == temp)
			return node;

	return NULL;
}

ListElement * list_search_id(LinkedList * list, int id)
{
	ListElement *temp;

	for (temp = list->head; temp; temp = temp->next)
		if (id == temp->key)
			return temp;

	return NULL;
}

ListElement * list_find(LinkedList * list, int key)
{
	ListElement *temp;
	for (temp = list->head; temp; temp = temp->next)
		if (temp->key == key)
			return temp;
	return NULL;
}

ListElement * list_delete(LinkedList * list, ListElement * node) {
	if (node->prev != NULL)
		node->prev->next = node->next;
	else
		list->head = node->next;

	if (node->next != NULL)
		node->next->prev = node->prev;

	return node; 
}

ListElement * list_minimum(LinkedList * list)
{
	ListElement *temp, *best = list->head;
	int min = list->head->key;
	for (temp = list->head; temp; temp = temp->next)
	{
		if (temp->key < min)
		{
			best = temp;
			min = temp->key;
		}
	}

	return best;
}

ListElement * list_maximum(LinkedList * list)
{
	ListElement *temp, *best = list->head;
	int max = list->head->key;
	for (temp = list->head; temp; temp = temp->next)
	{
		if (temp->key > max)
		{
			best = temp;
			max = temp->key;
		}
	}

	return best;
}

ListElement *list_successor(LinkedList * list, ListElement * node)
{
	ListElement *temp = NULL;
	ListElement *suc = NULL;

	for (temp = list->head; temp; temp = temp->next) {
		if (temp->key > node->key) {
			if (suc == NULL || (temp->key < suc->key)) {
				suc = temp;
			}
		}
	}

	return suc;
}

ListElement *list_predecessor(LinkedList * list, ListElement * node)
{
	ListElement *temp = NULL;
	ListElement *pred = NULL;

	for (temp = list->head; temp; temp = temp->next) {
		if (temp->key < node->key) {
			if ((pred == NULL || (temp->key > pred->key))) { 
				pred = temp;
			}
		}
	}

	return pred;
}

LinkedList * create_empty_list()
{
	LinkedList *list =  (LinkedList*) malloc(sizeof(LinkedList));
	list->head = NULL;
	return list;
}

ListElement * create_list_element(int key)
{
	ListElement *node = (ListElement*)malloc(sizeof(ListElement));
	node->key = key;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

// extra client code
int list_count(LinkedList * list)
{
	ListElement *temp;
	int count = 0;
	for (temp = list->head; temp; temp = temp->next)
		count++;
	return count;
}

void list_print(LinkedList * list)
{
	ListElement *temp;
	printf("[");
	for (temp = list->head; temp; temp = temp->next)
		printf("%d ", temp->key);
	printf("]\n");
}

void free_linked_list(LinkedList * list)
{
	ListElement *entry;
	entry = list->head;
	while (entry != NULL) {
		ListElement *next;
		next = entry->next;
		free(entry);
		entry = next;
	}
	free(list);
}

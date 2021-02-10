#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdio.h>
#include <stdbool.h>
typedef struct list_element_t {
	int key;
	struct list_element_t *prev;
	struct list_element_t *next;
} ListElement;

typedef struct linked_list {
	struct list_element_t *head;
} LinkedList;

// returns true if list is empty and false otherwise;
bool list_is_empty(LinkedList *list);

// inserts the node N into the list L, returns true if node was successfully inserted and false otherwise
bool list_insert(LinkedList *list, ListElement *node);

// returns a pointer to the node N if node is in the List L, and NULL if N is not on the list
ListElement *list_search(LinkedList *list, ListElement *node);

ListElement *list_search_id(LinkedList *list, int id);

// returns a pointer to the node N and N is deleted from the list, and NULL if deletion was not successful
ListElement *list_delete(LinkedList *list, ListElement *node);

// returns a pointer to the node with the smallest key
ListElement *list_minimum(LinkedList *list);

// returns a pointer to the node with the largest key.
ListElement *list_maximum(LinkedList *list);

// returns a pointer to the next larger node, or NULL if N is the maximum;
ListElement *list_successor(LinkedList *list, ListElement *node);

// returns a pointer to the next smaller node, or NULL if N is the minimum.
ListElement *list_predecessor(LinkedList *list, ListElement *node);

// returns number of elements in the list
LinkedList *create_empty_list();
ListElement *create_list_element(int key);
int list_count(LinkedList *list);
void list_print(LinkedList * list);
void free_linked_list(LinkedList *list);
#endif
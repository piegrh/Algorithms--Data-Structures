#include "LinkedList.h"
#include "Stack.h"

bool stack_is_empty(Stack *s)
{
	return (s->head == NULL);
}

bool stack_push(Stack *s, StackElement *n)
{
	StackElement *oldHead = s->head;
	s->head = n;
	s->head->next = oldHead;
	return true;
}

StackElement * stack_pop(Stack *s)
{
	StackElement *first = s->head;
	s->head = first->next;
	return first;
}

int stack_size(Stack * s)
{
	StackElement *tmp;
	int cnt = 0;
	for (tmp = s->head; tmp; tmp = tmp->next) 
		cnt++;
	return cnt;
}

void free_stack(Stack * s)
{
	StackElement *entry;
	entry = s->head;
	while (entry != NULL) {
		StackElement *next;
		next = entry->next;
		free(entry);
		entry = next;
	}
	free(s);
}

Stack * stack_create_empty()
{
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->head = NULL;
	return s;
}

StackElement * stack_create_element(int key)
{
	StackElement *entry = (StackElement*)malloc(sizeof(StackElement));
	entry->key = key;
	entry->next = NULL;
	return entry;
}

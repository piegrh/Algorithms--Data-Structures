#include <stdlib.h>
#include "Common.h"
#include "Queue.h"

bool queue_is_empty(Queue * q)
{
	return (q->head == NULL);
}

bool queue_enqueue(Queue * q, QueueElement *n)
{
	QueueElement *oldTail = q->tail;	

	q->tail = n;
	q->tail->next = NULL;

	if (queue_is_empty(q)) 
		q->head = q->tail;
	else 
		oldTail->next = q->tail;
	
	return true;
}

QueueElement * queue_dequeue(Queue * q)
{
	QueueElement *oldFirst = q->head;
	q->head = q->head->next;
	if (queue_is_empty(q)) {
		q->tail = NULL;
	} 
	return oldFirst;
}

int queue_size(Queue * q)
{
	QueueElement *tmp;
	int cnt = 0;
	for (tmp = q->head; tmp; tmp = tmp->next)
		cnt++;
	return cnt;
}

void free_queue(Queue * s)
{
	QueueElement *entry;
	entry = s->head;
	while (entry != NULL) {
		QueueElement *next;
		next = entry->next;
		free(entry);
		entry = next;
	}

	free(s);
}

Queue * queue_create_empty()
{
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;
	return q;
}

QueueElement * queue_create_node(int key)
{
	QueueElement *entry = (QueueElement*) malloc(sizeof(QueueElement));
	entry->key = key;
	entry->next = NULL;
	return entry;
}

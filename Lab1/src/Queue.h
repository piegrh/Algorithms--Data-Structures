#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

typedef struct queue_element_t {
	int key;
	struct queue_element_t *next;
} QueueElement;

typedef struct queue_t {
	QueueElement *head;
	QueueElement *tail;
} Queue;

 /*
  * Description: Determine if <q> is empty.
  * RETURN <bool>: TRUE if <q> is empty otherwise FALSE
  */
bool queue_is_empty(Queue *q);

 /*
  * Description: Adds <n> to the back of <q>
  * RETURN <bool>: TRUE if <n> was successfully added into <q>, otherwise FALSE
  */
bool queue_enqueue(Queue *q, QueueElement *n);

/*
 * Description: Dequeue the first QueueElement in <q>
 * RETURN <QueueElement>: The first QueueElement in <q>. NULL if <q> is empty.
 */
QueueElement *queue_dequeue(Queue *q);

/*
 * Description: Count number of QueueElements in q
 * RETURN <int>: number of QueueElements in q
 */
int queue_size(Queue *q);
void free_queue(Queue *q);
Queue *queue_create_empty();
QueueElement *queue_create_node(int key); 

#endif

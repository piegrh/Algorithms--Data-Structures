#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "QueueTest.h"
#include "Common.h"
#include "DebugLogger.h"

#define PERSON_NUM_LEN 13

// Returns true if all tests passed otherwise false
bool test_queue() {
	bool result = true;
	int i;
	char personNumber[PERSON_NUM_LEN] = "199111051257";
	Queue *s = (Queue*)malloc(sizeof(Queue));

	malloc_assert(s == NULL,__func__);

	s->head = NULL;
	s->tail = NULL;

	if (!queue_is_empty(s)) {
		debug_error("queue_is_empty FAIL (RESULT FALSE , EXPECTED TRUE)\n");
		result = false;
	}

	// Test Enqueue START
	debug_message("Enqueue: ");
	for (i = 0; i < PERSON_NUM_LEN - 1; i++)
	{
		QueueElement *tmp = (QueueElement*)malloc(sizeof(QueueElement));
		malloc_assert(tmp == NULL, __func__);
		tmp->key = personNumber[i] - '0';
		if (queue_enqueue(s, tmp)) {
			debug_message("%d ", tmp->key);
		}
		else {
			result = false;
			break;
		}
	}

	debug_message("\n");

	if (!check_size(queue_size(s), PERSON_NUM_LEN - 1))
		result = false;
	// Test Enqueue END

	// Test Dequeue START
	debug_message("Dequeue: ");
	for (i = 0; i < PERSON_NUM_LEN - 1; i++)
	{
		QueueElement *tmp;
		if (tmp = queue_dequeue(s)) {
			debug_message("%d ", tmp->key);
			if (tmp->key != personNumber[i] - '0') {
				result = false;
				debug_error("(Result %d, Expected %d)\n", tmp->key, personNumber[i] - '0');
			}
			free(tmp);
		} else {
			break;
		}
	}

	debug_message("\n");

	if (!check_size(queue_size(s), 0))
		result = false;
	// Test Dequeue END

	free_queue(s);

	return result;
}

static bool check_size(int size, int expected) {
	if (size != expected) {
		debug_error("size: %d expected %d\n", size, expected);
		return false;
	}
	return true;
}
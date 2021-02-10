#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "StackTest.h"
#include "Common.h"
#include "DebugLogger.h"

#define PERSON_NUM_LEN 13

// Returns true if all tests passed otherwise false
bool test_stack() {
	bool result = true;
	int i;
	char personNumber[PERSON_NUM_LEN] = "199111051257"; 
	Stack *s = (Stack*)malloc(sizeof(Stack));

	malloc_assert(s == NULL, __func__);

	s->head = NULL;

	if (!stack_is_empty(s)) {
		debug_error("stack_is_empty FAIL (RESULT FALSE , EXPECTED TRUE)\n");
		result = false;
	}

	// Test Push START
	debug_message("Push: ");
	for (i = 0; i < PERSON_NUM_LEN - 1; i++)
	{
		StackElement *tmp = (StackElement*)malloc(sizeof(StackElement));
		malloc_assert(tmp == NULL, __func__);
		tmp->key = personNumber[i] - '0';
		if (stack_push(s, tmp)) 
			debug_message("%d ", tmp->key);
	}

	debug_message("\n");

	if (!check_size(stack_size(s), PERSON_NUM_LEN - 1)) {
		result = false;
	}
	// Test Push END


	// Test Pop START
	debug_message("Pop: ");
	for (i = PERSON_NUM_LEN - 2; i >= 0; i--)
	{
		StackElement *tmp;
		if (tmp = stack_pop(s)) 
			debug_message("%d ", tmp->key);
		if (tmp->key != personNumber[i] - '0') {
			result = false;
			debug_error("(Result %d, Expected %d)\n", tmp->key, personNumber[i] - '0');
			break;
		}
		free(tmp);
	}

	debug_message("\n");

	if(!check_size(stack_size(s), 0)) 
		result = false;
	// Test Pop END

	free_stack(s);

	return result;
}

static bool check_size(int size, int expected) {
	if (size != expected) {
		debug_error("size: %d expected %d\n", size, expected);
		return false;
	}
	return true;
}
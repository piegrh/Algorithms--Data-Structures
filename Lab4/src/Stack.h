#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct stack_element_t {
	int key;
	struct stack_element_t *next;
} StackElement;

typedef struct stack_t {
	StackElement *head;
} Stack;

// Returns TRUE if stack <s> is empty otherwise FALSE
bool stack_is_empty(Stack *s);

/* 
 * Description: Adds <n> to the top of <s>
 * RETURN: <bool> TRUE if <n> was successfully added otherwise FALSE
 */
bool stack_push(Stack *s, StackElement *n);

/*
 * Description: Adds <n> to the top of <s>
 * RETURN <StackElement>: StackElement on top or NULL If <s> is empty 
 */
StackElement *stack_pop(Stack *s);

/*
 * Description: Counts all the elements in <s>
 * RETURN <int>: total number of elements in <s>
 */
int stack_size(Stack *s);
void free_stack(Stack *s);
Stack *stack_create_empty(); 
StackElement *stack_create_element(int i);
#endif
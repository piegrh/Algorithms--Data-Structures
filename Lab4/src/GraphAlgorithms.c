#include <stdlib.h>
#include "Common.h"
#include "GraphAlgorithms.h"
#include "DebugLogger.h"
#include "Queue.h"
#include "Stack.h"
#include <math.h>

#define FREE_CELL ' '
#define BLOCKED_CELL '#'
#define PATH_SRC 'S'
#define PATH_DEST 'X'
#define PATH_CHAR '.'
#define UNVISITED -1

static bool *create_bool_array(int n) {
	bool *visited = malloc(sizeof(bool) * n);
	malloc_assert(visited == NULL, __func__);
	for (int i = 0; i < n; i++)
		visited[i] = false;
	return visited;
}

static int *create_int_array(int n,int defaultValue) {
	int *arr = malloc(sizeof(int) * n);
	malloc_assert(arr == NULL, __func__);
	for (int i = 0; i < n; i++)
		arr[i] = defaultValue;
	return arr;
}

static double *create_double_array(int n, double defaultValue) {
	double *arr = malloc(sizeof(double) * n);
	malloc_assert(arr == NULL, __func__);
	for (int i = 0; i < n; i++)
		arr[i] = defaultValue;
	return arr;
}

static void DFS(Graph *g,Stack *s,Vertex *src,int *ids,int *low,bool *in_stack,int *id,int *cnt) {
	stack_push(s, stack_create_element(src->key));
	in_stack[src->key] = true;
	ids[src->key] = low[src->key] = *id;

	*id = *id + 1;

	Edge *temp = NULL;
	Vertex *dest = NULL;
	StackElement *entry = NULL;

	// Check neighbors
	for (temp = src->edges; temp; temp = temp->next) {
		if (ids[temp->dest] == UNVISITED) {
			dest = get_vertex(g, temp->dest);
			DFS(g,s,dest,ids,low,in_stack,id,cnt);
		}
		if (in_stack[temp->dest]) {
			low[src->key] = min(low[temp->dest], low[src->key]);
		}
	}

	if (ids[src->key] == low[src->key]) {
		printf("sub-graph %d [",*cnt + 1);
		for (entry = stack_pop(s);; entry = stack_pop(s)) {
			printf("%d, ", entry->key);
			in_stack[entry->key] = false;
			low[entry->key] = ids[src->key];
			if (entry->key == src->key) {
				free(entry);
				break;
			}
			free(entry);
		}
		printf("]\n");
		*cnt = *cnt + 1;
	}
}

// Tarjans Algorithm 
void SCC(Graph *g)
{
	int n = g->count+1,id, ssc_cnt;
	int *ids = create_int_array(n, UNVISITED);
	int *low = create_int_array(n, 0);
	bool *in_stack = create_bool_array(n);
	Stack *s = stack_create_empty();

	id = 0;
	ssc_cnt = 0;

	for (int i = 1; i <= n; i++) {
		if (ids[i] == UNVISITED) {
			DFS(g, s, get_vertex(g, i), ids, low, in_stack, &id, &ssc_cnt);
		}
	}

	free(ids);
	free(low);
	free(in_stack);
	free_stack(s);
}

// Bellman ford
void SSSP(Graph * g, Vertex * src)
{
	size_t n = g->count+1;
	double *d = create_double_array(n, INFINITY);
	Edge *temp = NULL;
	Edge *all_edges = get_all_edges(g);

	d[src->key] = 0;

	for (size_t i = 1; i < n; i++) {
		for (temp = all_edges; temp; temp = temp->next) {
			if ((d[temp->src] + temp->cost) < d[temp->dest]) {
				d[temp->dest] = d[temp->src] + temp->cost;
			}
		}
	}

	// Try to relax one more time 
	for (temp = all_edges; temp; temp = temp->next) {
		if ((d[temp->src] + temp->cost) < d[temp->dest]) {
			debug_warning("Negative cycle detected!\n");
			break;
		}
	}

	printf("Dest\tCost\n");
	for (size_t i = 1; i < n; i++) 
		printf("%d\t%fl\n", i, d[i]);

	free_edges(all_edges);
	free(d);
}

static int *BFS_solve(Graph *g,Vertex *src) {
	int n = g->count + 1;

	Queue *q = queue_create_empty();
	bool *visited = create_bool_array(n);
	int *prev = create_int_array(n,UNVISITED);

	Vertex *current = NULL;
	Edge *temp = NULL;
	QueueElement *element = NULL;

	visited[src->key] = true;
	queue_enqueue(q, queue_create_node(src->key));

	while (!queue_is_empty(q)) {
		element = queue_dequeue(q);
		current = get_vertex(g, element->key);
		free(element);
		for (temp = current->edges; temp; temp = temp->next) {
			if (!visited[temp->dest]) {
				queue_enqueue(q, queue_create_node(temp->dest));
				visited[temp->dest] = true;
				prev[temp->dest] = current->key;
			}
		}
	}

	free_queue(q);
	free(visited);

	return prev;
}

static LinkedList *BFS_create_path(Vertex *src,Vertex *dest, int *prev,int n) {
	LinkedList *list = create_empty_list();
	for (int i = dest->key; i != UNVISITED; i = prev[i])
		list_insert(list, create_list_element(i));
	return list;
}

static void print_row(int len, char c) {
	for (int i = 0; i < len; i++)
		printf("%c",c);
	printf("\n");
}

void render_path(Graph *g, LinkedList *path)
{
	int rows = (int)sqrt(g->count);

	char **map = malloc(sizeof(*map) * rows);
	malloc_assert(map == NULL, __func__);
	for (int i = 0; i < rows; i++) {
		map[i] = malloc(rows * sizeof(*(map[i])));
		malloc_assert(map[i] == NULL, __func__);
	}

	// ========= Render Map =========
	LinkedList *tempList;

	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < rows; y++) {
			tempList = get_neighbors(g, get_vertex(g, (x * rows) + y + 1));
			map[x][y] = list_count(tempList) == 0 ? BLOCKED_CELL : FREE_CELL;
			free_linked_list(tempList);
		}
	}

	// ========= Render Path =========
	ListElement *temp;

	if (path != NULL) {
		for (temp = path->head; temp; temp = temp->next) {
			map[(temp->key - 1) / rows][(temp->key - 1) % rows] = (temp->prev == NULL) ? PATH_SRC : (temp->next == NULL) ? PATH_DEST : PATH_CHAR;
		}
	}
	else {
		debug_warning("Path nullpointer!\n");
	}

	// ========= Draw Map =========

	print_row(rows + 2, BLOCKED_CELL);

	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < rows; y++) {
			if (y == 0) 
				printf("%c",BLOCKED_CELL);
			printf("%c", map[x][y]);
			if (y == rows-1) 
				printf("%c", BLOCKED_CELL);
		}
		printf("\n");
	}

	print_row(rows + 2, BLOCKED_CELL);


	// ========= Free map =========

	for (int i = 0; i < rows; i++) {
		free(map[i]);
	}
	free(map);
	map = NULL;
}

LinkedList *BFS(Graph * g, Vertex * src, Vertex * dest)
{
	int *prev = BFS_solve(g, src);
	LinkedList *path = BFS_create_path(src, dest, prev,g->count);
	free(prev);
	return path;
}

#include "LinkedList.h"
#include "Common.h"
#include "Graph.h"
#include <stdlib.h>
#include "DebugLogger.h"
#include <ctype.h>
#include <math.h>

Vertex *create_vertex(int key)
{
	Vertex *v = (Vertex*)malloc(sizeof(Vertex));
	v->key = key;
	v->edges = NULL;
	v->next = NULL;
	return v;
}

Graph * create_graph(int n)
{
	Graph *g = (Graph*) malloc(sizeof(Graph));
	malloc_assert(g == NULL, __func__);
	g->count = n;
	g->vertices = (Vertex**)malloc(sizeof(Vertex)*n);
	malloc_assert(g->vertices == NULL, __func__);

	for (int i = 0; i < n; i++) {
		g->vertices[i] = create_vertex(i + 1);
		if (i > 0) {
			g->vertices[i - 1]->next = g->vertices[i];
		}
	}

	return g;
}

int get_num_vertices(Graph * g)
{
	int cnt = 0;
	Vertex *temp;

	if (g->vertices != NULL) 
		for (temp = g->vertices[0]; temp; temp = temp->next)
			cnt++;

	// Update count
	if (cnt != g->count)
		g->count = cnt;

	return cnt;
}

int get_num_edges(Graph * g)
{
	Edge *temp;
	int cnt = g->count;
	int edge_num = 0;
	for (int i = 0; i < cnt; i++) {
		for (temp = g->vertices[i]->edges; temp; temp = temp->next) {
			edge_num++;
		}
	}
	return edge_num;
}

// Returns all vertices connected to node v with any edge
LinkedList * get_neighbors(Graph * g, Vertex * v)
{
	LinkedList *list = create_empty_list();
	for (size_t i = 1; i <= g->count; i++)
		if (has_edge(v, get_vertex(g, i)) || has_edge(get_vertex(g, i), v))
			list_insert(list, create_list_element(i));
	return list;
}

// Returns a list of all vertices v0 connected to node v with an edge (v0; v)
LinkedList * get_in_neighbors(Graph * g, Vertex * v)
{
	LinkedList *list = create_empty_list();
	for (size_t i = 1; i <= g->count; i++)
		if (has_edge(get_vertex(g, i), v))
			list_insert(list, create_list_element(i));
	return list;
}

// Returns a list of all vertices v0 connected to node v with an edge (v; v0)
LinkedList * get_out_neighbors(Graph * g, Vertex * v)
{
	LinkedList *list = create_empty_list();
	for (size_t i = 1; i <= g->count; i++)
		if (has_edge(v, get_vertex(g, i)))
			list_insert(list, create_list_element(i));
	return list;
}

Edge * get_all_edges(Graph * g)
{
	Edge* temp = NULL;
	Edge* newEdges = NULL;
	int cnt = 0;
	size_t n = g->count+1;

	for (size_t i = 1; i < n; i++) {
		for (temp = get_vertex(g, i)->edges; temp ;temp = temp->next) {
			if (newEdges == NULL) {
				newEdges = create_edge(temp->src, temp->dest, temp->cost);
			} else {
				get_last_edge(newEdges)->next = create_edge(temp->src, temp->dest, temp->cost);
			}
		}
	}

	return newEdges;
}

void add_directed_weighted_edge(Vertex * v, Vertex * u, double cost)
{
	if (v == NULL || u == NULL) {
		debug_warning("Tried to make an edge with a NULL-pointer.\n");
		return;
	}
	if (v->key <= 0 || u->key <= 0) {
		debug_warning("Index can not be lower than 1. (src=%d,dest=%d)\n",v->key,u->key);
		return;
	}

	Edge *edge = create_edge((v->key), (u->key), cost);

	if (v->edges == NULL) 
		v->edges = edge;
	else 
		(get_last_edge(v->edges))->next = edge;
}

void add_directed_unweighted_edge(Vertex * v, Vertex * u)
{
	add_directed_weighted_edge(v, u, 1.0);
}

void add_undirected_weighted_edge(Vertex * v, Vertex * u, double cost)
{
	add_directed_weighted_edge(v, u,cost);
	add_directed_weighted_edge(u, v,cost);
}

void add_undirected_unweighted_edge(Vertex * v, Vertex * u)
{
	add_directed_weighted_edge(v, u,1.0);
	add_directed_weighted_edge(u, v, 1.0);
}

bool has_edge(Vertex * v, Vertex * u)
{
	Edge *temp;
	for (temp = v->edges; temp; temp = temp->next) 
		if (temp->dest == u->key) 
			return true;
	return false;
}

// ================================================= Extra code1f

// Subtracts 1 from id
Vertex *get_vertex(Graph *g, int id) {
	if (id > (int)g->count || id < 1)
		return NULL;
	return g->vertices[id - 1];
}

// ================================================= Create from map Start


static bool set_cell(Graph *g, char *map[], int rows ,int src_x, int src_y, int offset_x, int offset_y)
{
	int dest_x = src_x + offset_x;
	int dest_y = src_y + offset_y;

	// valid point ?
	if ((dest_x >= 0 && dest_x < rows) && (dest_y >= 0 && dest_y < rows)) {
		// Blocked ?
		if (map[dest_x][dest_y] != 'X') {

			int src_id =  ( (rows * src_x) + src_y + 1);
			int dest_id = ( (rows * dest_x) + dest_y + 1);

			add_directed_unweighted_edge(
				get_vertex(g, src_id),
				get_vertex(g, dest_id)
			);
			return true;
		}
	}
	return false;
}

Graph *create_graph_map(int rows, char *map[])
{
	int size = rows * rows;
	Graph *g = create_graph(size);
	malloc_assert(g==NULL,__func__);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			if (map[i][j] == 'X')
				continue;
			set_cell(g, map, rows, i, j, -1, 0); // UP
			set_cell(g, map, rows, i, j, 1, 0); // DOWN
			set_cell(g, map, rows, i, j, 0, -1); // LEFT
			set_cell(g, map, rows, i, j, 0, 1); // RIGHT
		}
	}

	return g;
}

// ================================================= Create from map END

static Edge * create_edge(int src, int dest, double cost)
{
	Edge *e = (Edge*) malloc(sizeof(Edge));
	malloc_assert(e == NULL, __func__);
	e->dest = dest;
	e->cost = cost;
	e->src = src;
	e->next = NULL;
	return e;
}

static Edge * get_last_edge(Edge * edges)
{
	Edge *temp = edges;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}

// =================================== Free functions

void free_graph(Graph * g)
{
	Vertex *temp,*next;

	temp = g->vertices[0];
	
	while (temp != NULL) {
		next = temp->next;
		free_edges(temp->edges);
		free(temp);
		temp = next;
	}

	free(g->vertices);
	free(g);
	g = NULL;
}

void free_edges(Edge *edges) {
	Edge *temp = edges, *next = NULL;
	while (temp != NULL) {
		next = temp->next;
		free(temp);
		temp = next;
	}
	temp = NULL;
}

// =================================== Print functions

void print_graph(Graph * g)
{
	int cnt = g->count;
	printf("Vertex\tEdges\n");
	for (int i = 0; i < cnt; i++) {
		print_edges(g->vertices[i]);
	}
}

void print_graph_w(Graph * g)
{
	int cnt = g->count;
	printf("Vertex\tEdges\n");
	for (int i = 0; i < cnt; i++) {
		print_edges_w(g->vertices[i]);
	}
}

void print_edges(Vertex *v)
{
	printf("%d\t", v->key);
	Edge *temp;
	printf("[");
	for (temp = v->edges; temp; temp = temp->next) {
		printf("%d%s", temp->dest, temp->next == NULL ? "" : ",");
	}
	printf("]\n");
}

void print_edges_w(Vertex * v)
{
	printf("%d\t", v->key);
	Edge *temp;
	printf("[");
	for (temp = v->edges; temp; temp = temp->next) {
		printf("[%d,%fl]%s", temp->dest,temp->cost, temp->next == NULL ? "" : ",");
	}
	printf("]\n");
}

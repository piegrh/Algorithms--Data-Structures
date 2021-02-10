#ifndef GRAPH_H
#define GRAPH_H

#include "LinkedList.h"
#include <stdbool.h>

typedef struct edge_t {
	int src,dest;
	double cost;
	struct edge_t *next;
}Edge;

typedef struct vertex_t {
	int key;
	struct edge_t *edges;
	struct vertex_t *next;
} Vertex;

typedef struct graph_t {
	size_t count;
	Vertex **vertices;
} Graph;

// Create and return a graph containing n vertices (each vertex is an integer between 1 and n).
Graph *create_graph(int n);

/*
 * You can also use Graph->count if you have not manually
 * added vertices or changed the value.
 *
 * Returns the number of vertices in graph G
 */
int get_num_vertices(Graph *g);

//Returns the total number of edges of graph G
int get_num_edges(Graph *g);

//Returns all vertices connected to node v with any edge
LinkedList * get_neighbors(Graph *g,Vertex *v);

// Returns a list of all vertices v0 connected to node v with an edge (v0, v)
LinkedList * get_in_neighbors(Graph *g, Vertex *v);

// Returns a list of all vertices v0 connected to node v with an edge(v, v0)
LinkedList * get_out_neighbors(Graph *g, Vertex *v);

// Returns all edges in Graph g
Edge * get_all_edges(Graph *g);

void add_directed_weighted_edge(Vertex * src, Vertex * dest, double cost);
void add_undirected_weighted_edge(Vertex * src, Vertex * dest, double cost);
void add_directed_unweighted_edge(Vertex * src, Vertex * dest);
void add_undirected_unweighted_edge(Vertex * src, Vertex * dest);

// Returns TRUE if there is an edge between v1 and v2 and FALSE otherwise.
bool has_edge(Vertex * v, Vertex * u);

// ============== Extra client code ======================

/*
 * Takes an two-dimensional array of chars and creates
 * a graph.
 *
 * Use x to indicate a blocked cell.
 * anything else is considered walkable.
 *
 * Maps must be quadratic (for now).
 */
Graph *create_graph_map(int n, char *map[]);
// returns vertex with matching key. Null if not found
Vertex *get_vertex(Graph *g, int key);
// Print unweighted Graph
void print_graph(Graph * g);
// Print weighted Graph
void print_graph_w(Graph * g);
// Print unweighted edges
void print_edges(Vertex * v);
// Print weighted edges
void print_edges_w(Vertex * v);
void free_graph(Graph * g);
void free_edges(Edge *edges);
// ====================== "Private" functions ======================
static Edge *create_edge(int src,int dest, double cost);
static Edge *get_last_edge(Edge *edges);

#endif
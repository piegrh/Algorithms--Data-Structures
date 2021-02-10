#ifndef GRAPH_ALGORITHMS
#define GRAPH_ALGORITHMS
#include "Graph.h"

 // finds the shortest path from src to dest
LinkedList *BFS(Graph *g,Vertex *src, Vertex *dest);

// finds all sub-graphs in graph g
void SCC(Graph *g);

// Finds the shortest path to any connected node from src
void SSSP(Graph *g, Vertex *src);

// Print path. Use BFS to find path
void render_path(Graph *g, LinkedList *path);

// static functions
static bool *create_bool_array(int n);
static double *create_double_array(int n, double defaultValue);
static int *create_int_array(int n, int defaultValue);
static void print_row(int len, char c);
#endif
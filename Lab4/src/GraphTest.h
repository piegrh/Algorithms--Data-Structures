#include <stdbool.h>
#ifndef GRAPH_TEST_H
#define GRAPH_TEST_H
bool test_graph(void);
static bool eval_results(int result, int expected, char *name);
static bool test_get_num_vertices(void);
static bool test_get_num_edges(void);
static bool test_get_neighbors(void);
static bool test_get_in_neighbors(void);
static bool test_get_out_neighbors(void);
#endif
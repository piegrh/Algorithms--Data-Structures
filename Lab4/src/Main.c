#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "GraphTest.h"
#include "DebugLogger.h"
#include "GraphAlgorithms.h"

#define COL 10
#define GRAPH_4_1_SRC 1
#define GRAPH_4_2_SRC 2

static void print_line() {
	printf("-------------------------------------------\n");
}

static void print_line_2() {
	printf("\n==========================================\n");
}

int main(void) {
	if (test_graph()) {
		debug_message("Graph test passed!\n");
	}

	// Exercise 2, Shortest Paths
	char *map[COL] =
	{
		"....X.....",
		"....X.....",
		"....X.....",
		"....X.....",
		"....XXXXX.",
		"....X.....",
		"....X.....",
		"....X.....",
		".XXXX.....",
		"..........",
	};

	printf("2)Shortest Paths from (1,1) to (6,1)\n");
	Graph *g = create_graph_map(COL, map);
	LinkedList *path = BFS(g, get_vertex(g, 1), get_vertex(g, 6));
	render_path(g, path);
	free_linked_list(path);
	free_graph(g);

	//Exercise 3, Connectivity
	print_line_2();
	printf("\n3) Connectivity\n");
	g = create_graph(10);

	// <IMAGE HERE>

	// Graph #1
	add_directed_unweighted_edge(get_vertex(g, 1), get_vertex(g, 2));
	add_directed_unweighted_edge(get_vertex(g, 2), get_vertex(g, 3));
	add_directed_unweighted_edge(get_vertex(g, 3), get_vertex(g, 4));
	add_directed_unweighted_edge(get_vertex(g, 4), get_vertex(g, 1));
	add_directed_unweighted_edge(get_vertex(g, 5), get_vertex(g, 6));
	add_directed_unweighted_edge(get_vertex(g, 6), get_vertex(g, 7));
	add_directed_unweighted_edge(get_vertex(g, 7), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 8), get_vertex(g, 9));
	add_directed_unweighted_edge(get_vertex(g, 3), get_vertex(g, 10));
	add_directed_unweighted_edge(get_vertex(g, 5), get_vertex(g, 4));
	add_directed_unweighted_edge(get_vertex(g, 8), get_vertex(g, 7));

	print_graph(g);
	print_line();
	SCC(g);
	free_graph(g);

	//Exercise 4, Single-Source Shortest Paths

	print_line_2();

	printf("\n4) Single-Source Shortest Paths\n");

	// Graph #1
	printf("4) Graph #1\n");

	g = create_graph(5);
	add_directed_weighted_edge(get_vertex(g, 1), get_vertex(g, 2), 15.0);
	add_directed_weighted_edge(get_vertex(g, 1), get_vertex(g, 3), 8.0);
	add_directed_weighted_edge(get_vertex(g, 1), get_vertex(g, 4), 5.0);
	add_directed_weighted_edge(get_vertex(g, 4), get_vertex(g, 3), -2.0);
	add_directed_weighted_edge(get_vertex(g, 4), get_vertex(g, 5), 9.0);
	add_directed_weighted_edge(get_vertex(g, 3), get_vertex(g, 2), 1.0);
	add_directed_weighted_edge(get_vertex(g, 3), get_vertex(g, 5), 8.0);
	add_directed_weighted_edge(get_vertex(g, 5), get_vertex(g, 5), 8.0);

	print_graph_w(g);
	print_line();
	printf("Src = %d\n", GRAPH_4_1_SRC);
	SSSP(g, get_vertex(g, GRAPH_4_1_SRC));

	free_graph(g);

	print_line_2();

	// Graph #2
	g = create_graph(7);
	printf("\n4) Graph #2\n");

	add_directed_weighted_edge(get_vertex(g, 1), get_vertex(g, 2), 10);
	add_directed_weighted_edge(get_vertex(g, 1), get_vertex(g, 3), 2);
	add_directed_weighted_edge(get_vertex(g, 2), get_vertex(g, 5), 5);
	add_directed_weighted_edge(get_vertex(g, 3), get_vertex(g, 4), 1);
	add_directed_weighted_edge(get_vertex(g, 4), get_vertex(g, 1), -4);
	add_directed_weighted_edge(get_vertex(g, 4), get_vertex(g, 6), 1);
	add_directed_weighted_edge(get_vertex(g, 5), get_vertex(g, 3), -20);
	add_directed_weighted_edge(get_vertex(g, 5), get_vertex(g, 6), 3);
	add_directed_weighted_edge(get_vertex(g, 5), get_vertex(g, 7), 1);
	add_directed_weighted_edge(get_vertex(g, 6), get_vertex(g, 7), 4);

	print_graph_w(g);
	print_line();
	printf("Src = %d\n", GRAPH_4_2_SRC);
	SSSP(g, get_vertex(g, GRAPH_4_2_SRC));
	print_line_2();
	free_graph(g);
	getchar();
	return 0;
}
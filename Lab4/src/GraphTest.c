#include "DebugLogger.h"
#include "GraphTest.h"
#include "Graph.h"
#include <stdlib.h>

#define TEST_NUM 5

bool test_graph(void)
{

	int i;
	bool test[TEST_NUM] =
	{
		test_get_num_vertices(),
		test_get_num_edges(),
		test_get_neighbors(),
		test_get_in_neighbors(),
		test_get_out_neighbors()
	};

	for (i = 0; i < TEST_NUM; i++)
		if (!test[i])
			return false;

	return true;
}

static bool eval_results(int result,int expected,char *name)
{
	if (result == expected) {
		debug_message("%s passed!\n", name);
		return true;
	}
	debug_error("%s failed! (result = %d, expected = %d)\n", name,result,expected);
	return false;
}

static bool test_get_num_vertices(void)
{
	int expected = 10;
	int result;

	// https://i.imgur.com/SIskQeS.png <-- graph image
	Graph *g = create_graph(10);
	add_undirected_unweighted_edge(get_vertex(g, 1), get_vertex(g, 2));
	add_undirected_unweighted_edge(get_vertex(g, 1), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 2), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 2), get_vertex(g, 3));
	add_undirected_unweighted_edge(get_vertex(g, 3), get_vertex(g, 4));
	add_undirected_unweighted_edge(get_vertex(g, 5), get_vertex(g, 4));
	add_undirected_unweighted_edge(get_vertex(g, 6), get_vertex(g, 4));

	result = get_num_vertices(g);
	free_graph(g);

	return eval_results(result,expected,__func__);
}

static bool test_get_num_edges(void)
{
	int expected = 14;
	int result;

	Graph *g = create_graph(10);
	add_undirected_unweighted_edge(get_vertex(g, 1), get_vertex(g, 2));
	add_undirected_unweighted_edge(get_vertex(g, 1), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 2), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 2), get_vertex(g, 3));
	add_undirected_unweighted_edge(get_vertex(g, 3), get_vertex(g, 4));
	add_undirected_unweighted_edge(get_vertex(g, 5), get_vertex(g, 4));
	add_undirected_unweighted_edge(get_vertex(g, 6), get_vertex(g, 4));

	result = get_num_edges(g);

	free_graph(g);
	return eval_results(result, expected, __func__);
}

static bool test_get_neighbors(void)
{
	bool result = true;
	ListElement *temp, *next;

	LinkedList *resultList = NULL, *list = create_empty_list();
	list_insert(list, create_list_element(1));
	list_insert(list, create_list_element(2));
	list_insert(list, create_list_element(4));
	list_insert(list, create_list_element(7));
	list_insert(list, create_list_element(8));

	Graph *g = create_graph(10);
	add_undirected_unweighted_edge(get_vertex(g, 1), get_vertex(g, 2));
	add_undirected_unweighted_edge(get_vertex(g, 1), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 2), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 2), get_vertex(g, 3));
	add_undirected_unweighted_edge(get_vertex(g, 3), get_vertex(g, 4));
	add_undirected_unweighted_edge(get_vertex(g, 5), get_vertex(g, 4));
	add_undirected_unweighted_edge(get_vertex(g, 6), get_vertex(g, 4));
	add_directed_unweighted_edge(get_vertex(g, 7), get_vertex(g, 5)); 
	add_directed_unweighted_edge(get_vertex(g, 5), get_vertex(g, 8)); 

	resultList = get_neighbors(g, get_vertex(g, 5));

	temp = list->head;

	while (temp != NULL) {
		if (!list_search_id(resultList, temp->key)) {
			result = false;
			break;
		}
		next = temp->next;
		list_delete(list, temp);
		free(temp);
		temp = next;
	}

	if (!list_is_empty(list)) {
		result = false;
	}

	free_linked_list(list);
	free_linked_list(resultList);
	free_graph(g);

	return eval_results(result ? 1 : 0, 1, __func__);
}

static bool test_get_in_neighbors(void)
{
	bool result = true;
	ListElement *temp, *next;

	LinkedList *resultList = NULL, *list = create_empty_list();
	list_insert(list, create_list_element(1));
	list_insert(list, create_list_element(2));
	list_insert(list, create_list_element(4));
	list_insert(list, create_list_element(7));

	Graph *g = create_graph(10);
	add_undirected_unweighted_edge(get_vertex(g, 1), get_vertex(g, 2));
	add_undirected_unweighted_edge(get_vertex(g, 1), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 2), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 2), get_vertex(g, 3));
	add_undirected_unweighted_edge(get_vertex(g, 3), get_vertex(g, 4));
	add_undirected_unweighted_edge(get_vertex(g, 5), get_vertex(g, 4));
	add_undirected_unweighted_edge(get_vertex(g, 6), get_vertex(g, 4));
	add_directed_unweighted_edge(get_vertex(g, 7), get_vertex(g, 5));
	add_directed_unweighted_edge(get_vertex(g, 5), get_vertex(g, 8));

	resultList = get_in_neighbors(g, get_vertex(g, 5));

	temp = list->head;

	while (temp != NULL) {
		if (!list_search_id(resultList, temp->key)) {
			result = false;
			break;
		}
		next = temp->next;
		list_delete(list, temp);
		free(temp);
		temp = next;
	}

	if (!list_is_empty(list)) {
		result = false;
	}

	free_linked_list(list);
	free_linked_list(resultList);
	free_graph(g);

	return eval_results(result ? 1 : 0, 1, __func__);
}

static bool test_get_out_neighbors(void)
{
	bool result = true;
	ListElement *temp,*next;

	LinkedList *resultList = NULL, *list = create_empty_list();
	list_insert(list, create_list_element(1));
	list_insert(list, create_list_element(2));
	list_insert(list, create_list_element(4));
	list_insert(list, create_list_element(8));

	Graph *g = create_graph(10);
	add_undirected_unweighted_edge(get_vertex(g, 1), get_vertex(g, 2));
	add_undirected_unweighted_edge(get_vertex(g, 1), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 2), get_vertex(g, 5));
	add_undirected_unweighted_edge(get_vertex(g, 2), get_vertex(g, 3));
	add_undirected_unweighted_edge(get_vertex(g, 3), get_vertex(g, 4));
	add_undirected_unweighted_edge(get_vertex(g, 5), get_vertex(g, 4));
	add_undirected_unweighted_edge(get_vertex(g, 6), get_vertex(g, 4));
	add_directed_unweighted_edge(get_vertex(g, 7), get_vertex(g, 5));
	add_directed_unweighted_edge(get_vertex(g, 5), get_vertex(g, 8));

	resultList = get_out_neighbors(g, get_vertex(g, 5));

	temp = list->head;

	while (temp != NULL) {
		if (!list_search_id(resultList, temp->key)) {
			result = false;
			break;
		}
		next = temp->next;
		list_delete(list, temp);
		free(temp);
		temp = next;
	}

	if (!list_is_empty(list)) {
		result = false;
	}

	free_linked_list(list);
	free_linked_list(resultList);
	free_graph(g);

	return eval_results(result ? 1 : 0, 1, __func__);
}

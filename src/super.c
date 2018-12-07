#include "lem_in.h"

static int		flow_to_vertex(t_list *vertex, int vtx_id)
{
	int		count;
	t_edge	*edge;

	count = 0;
	if (DEBUG)
		ft_printf("DEBUG: Counting edges which flow to vertex %d.\n", vtx_id);
	while (vertex)
	{
		edge = ((t_edge*)(vertex->content))->rev;
		if (DEBUG)
			ft_printf("\t...now looking at %d->%d. Flow %d.\n", edge->source, edge->sink, edge->flow);
		if (edge->flow == 1)
			count++;
		vertex = vertex->next;
	}
	if (DEBUG)
		ft_printf("%d edge%sflow%sto %d.\n", count, (count > 1 ? "s " : " "), (count < 2 ? "s " : " "), vtx_id);
	return (count);
}

/* t_edge			*edge_to_preserve(t_listarray graph, int start_id, int vtx) */
/* { */
/* 	t_list	*vertex; */
/* 	int		min_path_length; */
/* 	t_edge	*edge; */
/* 	int		min_tmp; */
/* 	t_edge	*shortest_path; */

/* 	vertex = (graph)[vtx]; */
/* 	min_path_length = 2147483647; */
/* 	while (vertex) */
/* 	{ */
/* 		edge = ((t_edge*)(vertex->content))->rev; */
/* 		if (edge->flow == 1) */
/* 		{ */
/* 			min_tmp = 1 + count_back_length((graph), edge->source, start_id); */
/* 			if (min_tmp < min_path_length) */
/* 			{ */
/* 				min_path_length = min_tmp; */
/* 				shortest_path = edge; */
/* 			} */
/* 		} */
/* 		vertex = vertex->next; */
/* 	} */
/* 	if (DEBUG) */
/* 		ft_printf("\tDEBUG: Shortest path goes %d->%d.\n", shortest_path->source, shortest_path->sink); */
/* 	return (edge); */
/* } */

void			zero_path(t_list *vertex, t_listarray graph, int sink)
{
	t_edge	*edge;

	if (DEBUG)
		ft_printf("DEBUG: Zeroing out path.\n");
	while (vertex != graph[sink])
	{
		edge = ((t_edge*)(vertex->content));
		while (edge->flow != 1)
		{
			vertex = vertex->next;
			if (!vertex)
				break ;
			edge = ((t_edge*)(vertex->content));
		}
		if (DEBUG)
			print_edge(edge);
		edge->flow = 0;
		vertex = graph[edge->sink];
	}
}

/* void			flow_zero(t_listarray graph, t_edge *leave_alone, int vtx, int start_id) */
/* { */
/* 	t_list	*vertex; */
/* 	t_edge	*edge; */

/* 	if (DEBUG) */
/* 		ft_printf("DEBUG: Clearing superposed paths around vertex %d.\n", vtx); */
/* 	vertex = (graph)[vtx]; */
/* 	while (vertex) */
/* 	{ */
/* 		edge = ((t_edge*)(vertex->content))->rev; */
/* 		if (edge->flow == 1 && edge != leave_alone) */
/* 		{ */
/* 			if (DEBUG) */
/* 				ft_printf("\t...found one.\n"); */
/* 			zero_path(vtx, start_id, graph); */
/* 		} */
/* 		vertex = vertex->next; */
/* 	} */
/* } */

/* int			prevent_superpositions(t_listarray graph, int start_id, int map_size, int end_id) */
/* { */
/* 	int		i; */
/* 	int		count; */
/* 	t_list	*vertex; */
/* 	int		ret; */

/* 	ret = 0; */
/* 	if (DEBUG) */
/* 		ft_printf("DEBUG: Checking superposed paths.\n"); */
/* 	i = -1; */
/* 	while (++i < map_size) */
/* 	{ if (i == start_id || i == end_id) */
/* 			continue ; */
/* 		vertex = (graph)[i]; */
/* 		count = flow_to_vertex(vertex, i); */
/* 		if (count > 1) */
/* 		{ */
/* 			ret++; */
/* 			if (DEBUG) */
/* 				ft_printf("\tFlagged vertex %d.\n", i); */
/* 			flow_zero(graph, edge_to_preserve(graph, start_id, i), i, start_id); */
/* 		} */
/* 	} */
/* 	return (ret); */
/* } */

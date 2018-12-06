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

static int		prev_vertex_id(t_list *vertex)
{
	t_edge	*edge;

	edge = (t_edge*)(vertex->content)->rev;
	while (edge->flow != 1)
	{
		vertex = vertex->next;
		edge = (t_edge*)(vertex->content)->rev;
	}
	return (edge->source);
}

static int		count_back_length(t_list **graph, int source, int sink)
{
	int		len;
	t_list	*vertex;

	len = 1;
	vertex = (graph)[source];
	while (vertex != (graph)[sink])
	{
		len++;
		vertex = (graph)[prev_vertex_id(vertex)];
	}
	return (len);
}

static void		flow_zero(t_list ***graph, int start_id, int vtx)
{
	t_list	*vertex;
	int		min_path_length;
	t_edge	*shortest_path;
	int		min_tmp;

	vertex = graph[vtx];
	min_path_length = 2147483647;
	while (vertex)
	{
		shortest_path = ((t_edge*)(vertex->content))->rev;
		if (shortest_path->flow == 1)
		{
			min_tmp = 1 + count_back_length((*graph)[shortest_path->source], shortest_path->source, start_id);
			if (min_tmp < min_path_length)
			{
				min_path_length = min_tmp;
		}
	}
}

void			prevent_superpositions(t_list ***graph, int start_id, int map_size, int end_id)
{
	int		i;
	int		count;
	t_list	*vertex;

	if (DEBUG)
		ft_printf("DEBUG: Checking superposed paths.\n");
	i = -1;
	while (++i < map_size)
	{
		if (i == start_id || i == end_id)
			continue ;
		vertex = (*graph)[i];
		count = flow_to_vertex(vertex, i);
		if (count > 2)
		{
			if (DEBUG)
				ft_printf("\tFlagged vertex %d.\n", i);
			flow_zero(graph, start_id, i);
		}
	}
}

#include "lem_in.h"

static int		flow_to_vertex(t_list *vertex)
{
	int		count;
	t_edge	*edge;

	count = 0;
	while (vertex)
	{
		edge = ((t_edge*)(vertex->content))->rev;
		if (DEBUG)
			ft_printf("\t...now looking at %d->%d. Flow %d.\n", edge->source, edge->sink, edge->flow);
		if (edge->flow == 1)
			count++;
		vertex = vertex->next;
	}
	return (count);
}

/* t_edge			*edge_to_preserve(t_listarray graph, int start_id, int vtx)
{
	t_list	*vertex;
	int		min_path_length;
	t_edge	*edge;
	int		min_tmp;
	t_edge	*shortest_path;

	vertex = (graph)[vtx];
	min_path_length = 2147483647;
	while (vertex)
	{
		edge = ((t_edge*)(vertex->content))->rev;
		if (edge->flow == 1)
		{
			min_tmp = 1 + count_back_length((graph), edge->source, start_id);
			if (min_tmp < min_path_length)
			{
				min_path_length = min_tmp;
				shortest_path = edge;
			}
		}
		vertex = vertex->next;
	}
	if (DEBUG)
		ft_printf("\tDEBUG: Shortest path goes %d->%d.\n", shortest_path->source, shortest_path->sink);
	return (edge);
} */

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

/* void			flow_zero(t_listarray graph, t_edge *leave_alone, int vtx, int start_id)
{
	t_list	*vertex;
	t_edge	*edge;

	if (DEBUG)
		ft_printf("DEBUG: Clearing superposed paths around vertex %d.\n", vtx);
	vertex = (graph)[vtx];
	while (vertex)
	{
		edge = ((t_edge*)(vertex->content))->rev;
		if (edge->flow == 1 && edge != leave_alone)
		{
			if (DEBUG)
				ft_printf("\t...found one.\n");
			zero_path(vtx, start_id, graph);
		}
		vertex = vertex->next;
	}
} */

t_bool			path_is_super(t_listarray graph, int end_id, t_list *vertex)
{
	int		count;

	if (DEBUG)
		ft_printf("DEBUG: Checking superposed paths.\n");
	while (vertex != graph[end_id])
	{
		count = flow_to_vertex(vertex);
		if (count > 1)
			return (true);
		vertex = graph[next_vertex_id(vertex)];
	}
	return (false);
}

int				clear_super_paths(t_listarray graph, t_list *start, int end_id)
{
	int		ret;
	int		sink_vtx;

	ret = 0;
	while (start)
	{
		if (((t_edge*)(start->content))->flow)
		{
			sink_vtx = ((t_edge*)(start->content))->source;
			if (path_is_super(graph, end_id, graph[sink_vtx]))
			{
				if (DEBUG)
					ft_printf("\tFlagged vertex %d.\n", sink_vtx);
				zero_path(graph[sink_vtx], graph, end_id);
				ret++;
			}
		}
		start = start->next;
	}
	return (ret);
}

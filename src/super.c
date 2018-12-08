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

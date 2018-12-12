#include "lem_in.h"

static inline int	expected_lines(int ants, int flow, int avg)
{
	return ((ants - 1) / flow + avg);
}

void				lemin_upd_paths(t_lemin *lemin, int *sizes, int tabsize)
{
	int		idx;

	idx = 0;
	while (idx < tabsize)
	{
		ft_lstappend(&lemin->path_lengths, \
				ft_lstnew(&sizes[idx], sizeof(int)));
		idx++;
	}
}

int					print_path_analysis(t_listarray graph, t_lemin *lemin)
{
	int		*lengths;
	int		avg_len;
	int		ret;

	lengths = size_paths(graph, lemin);
	avg_len = ft_tab_avg(lengths, lemin->flow);
	ret = expected_lines(lemin->ants, lemin->flow, avg_len);
	if (DEBUG)
	{
		ft_printf("DEBUG: Avg path length: %d.\n", avg_len);
		ft_printf("\tExpecting %d lines to solve.\n", ret);
	}
	ft_lstdel(&lemin->path_lengths, &ft_free_node);
	ft_memdel((void**)&lengths);
	return (ret);
}

void				del_edge(t_listarray graph, t_edge to_del)
{
	t_list	*vertex;
	t_edge	edge;

	vertex = graph[to_del.source];
	edge = *((t_edge*)(vertex->content));
	while (edge.sink != to_del.sink)
	{
		vertex = vertex->next;
		edge = *((t_edge*)(vertex->content));
	}
	if (DEBUG)
	{
		ft_putendl("Want to delete:");
		print_edge(&to_del);
		ft_putendl("Have found:");
		print_edge(&edge);
	}
	ft_lstpluck(&graph[to_del.source], &vertex, &ft_free_node);
}

void				cxl_super(t_listarray graph, t_edge *edge, int end)
{
	zero_path(graph[edge->source], graph, end);
	del_edge(graph, *(edge->rev));
	del_edge(graph, *edge);
}

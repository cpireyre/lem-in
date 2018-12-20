/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:46:52 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/17 15:51:37 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

/*
**	t_list **graph = vertices
**	t_list *queue = vertices to be visited on each pass of the BFS
*/

static inline t_bool	edge_is_valid(t_edge *edge, t_edge **path, int src)
{
	if (!((path)[edge->sink]) && edge->sink != src && edge->flow < 1)
		return (true);
	else
		return (false);
}

void					bfs_step(t_edge ***path, t_list **queue, \
t_list **graph, int source)
{
	t_list	*current_vertex;
	t_edge	*edge;
	int		vertex_no;
	t_list	*tmp;

	vertex_no = *(int*)(*queue)->content;
	current_vertex = graph[vertex_no];
	if (DEBUG > 3)
		ft_printf("\tVisiting vertex %d.\n", vertex_no);
	while (current_vertex)
	{
		edge = (t_edge*)current_vertex->content;
		if (edge_is_valid(edge, *path, source))
		{
			(*path)[edge->sink] = edge;
			ft_lstappend(queue, ft_lstnew(&edge->sink, sizeof(int)));
			if (DEBUG > 3)
				ft_printf("\t\tEnqueued vertex %d,\n", edge->sink);
		}
		current_vertex = current_vertex->next;
	}
	tmp = (*queue)->next;
	ft_lstdelone(queue, &ft_free_node);
	*queue = tmp;
}

t_edge					**breadth_first_search(t_listarray graph, int source, \
int sink, int size)
{
	t_edge	**path;
	t_list	*queue;

	path = ft_memalloc(sizeof(t_edge*) * size);
	queue = ft_lstnew(&source, sizeof(int));
	if (DEBUG > 2)
		ft_putendl("DEBUG: Commencing breadth-first search.");
	while (queue)
		bfs_step(&path, &queue, graph, source);
	if (DEBUG > 2 && path[sink])
		ft_printf("DEBUG: BFS done. path[sink] flows from %d to %d.", \
path[sink]->source, path[sink]->sink);
	if (!path[sink])
	{
		ft_memdel((void**)&path);
		return (NULL);
	}
	return (path);
}

t_bool					flow_through_path(t_listarray graph, \
		t_edge **path, int start, int end)
{
	t_edge	*edge;
	t_bool	super;

	super = false;
	edge = path[end];
	flow_thru_edge(edge);
	if (edge->source == start)
		return (false);
	edge = path[edge->source];
	while (edge->source != start && !super)
	{
		flow_thru_edge(edge);
		if ((super = flow_to_vertex(graph[edge->sink]) > 1))
			break ;
		edge = path[edge->source];
	}
	flow_thru_edge(edge);
	return (super);
}

int						edmonds_karp(t_listarray graph, t_lemin *lemin, \
		int stop)
{
	t_edge	**path;
	int		ret;
	int		tmp;
	int		min;

	min = INT_MAX;
	ret = 0;
	while (stop != lemin->flow && (path = breadth_first_search(graph, \
					lemin->start_id, lemin->end_id, lemin->map_size)))
	{
		if (flow_through_path(graph, path, lemin->start_id, lemin->end_id))
			ft_memdel((void**)&path);
		else
		{
			lemin->flow++;
			tmp = print_path_analysis(graph, lemin);
			if (tmp < min)
			{
				min = tmp;
				ret = lemin->flow;
			}
			ft_memdel((void**)&path);
		}
	}
	return (ret);
}

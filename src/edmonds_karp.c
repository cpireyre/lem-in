/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:46:52 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/05 14:34:54 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	t_list **graph = vertices
**	t_list *queue = vertices to be visited on each pass of the BFS
*/

static inline t_bool		edge_is_valid(t_edge *edge, t_edge **path, int src)
{
	if (!((path)[edge->sink]) && edge->sink != src && edge->flow < 1)
		return (true);
	else
		return (false);
}

void		bfs_step(t_edge ***path, t_list **queue, t_list **graph, int source)
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

t_edge		**breadth_first_search(t_listarray graph, int source, int sink, int size)
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

void		flow_through_path(t_edge **path, int start, int end)
{
	t_edge	*edge;

	edge = path[end];
	while (edge->source != start)
	{
		edge->flow += 1;
		edge->rev->flow -= 1;
		edge = path[edge->source];
	}
	edge->flow += 1;
	edge->rev->flow -= 1;
}

int			edmonds_karp(t_listarray max_flow_network, t_lemin *lemin)
{
	t_edge	**path;
	int		max_flow;

	max_flow = 0;
	while ((path = breadth_first_search(max_flow_network, \
					lemin->start_id, lemin->end_id, lemin->map_size)))
	{
		flow_through_path(path, lemin->start_id, lemin->end_id);
		max_flow++;
		lemin->flow = max_flow;
		free(size_paths(max_flow_network, lemin));
		ft_memdel((void**)&path);
	}
	return (max_flow);
}

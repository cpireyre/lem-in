/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:46:50 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/05 14:47:35 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	fill_edge(t_edge *edge, int source, int sink)
{
	edge->source = source;
	edge->sink = sink;
	edge->flow = 0;
	edge->rev = NULL;
}

static void	add_connections_to_graph(t_list **vertex, int vtx_nb, char *links)
{
	t_edge	tmp;
	int		i;

	i = 0;
	while (links[i])
	{
		if (links[i] == CONNECTED)
		{
			fill_edge(&tmp, vtx_nb, i);
			ft_lstappend(vertex, ft_lstnew(&tmp, sizeof(t_edge)));
		}
		i++;
	}
}

static void	hook_up_rev_edges(t_list **graph, int vertices)
{
	t_list	*edges_from_vertex;
	t_list	*edge_to_update;
	int		i;
	int		cur_edge_t;

	i = 0;
	while (i < vertices)
	{
		edges_from_vertex = graph[i];
		while (edges_from_vertex)
		{
			if (((t_edge*)(edges_from_vertex->content))->rev == NULL)
			{
				cur_edge_t = ((t_edge*)(edges_from_vertex->content))->sink;
				edge_to_update = graph[cur_edge_t];
				while (((t_edge*)(edge_to_update->content))->sink != i)
					edge_to_update = edge_to_update->next;
				((t_edge*)edge_to_update->content)->rev = (t_edge*)edges_from_vertex->content;
				((t_edge*)edges_from_vertex->content)->rev = (t_edge*)edge_to_update->content;
			}
			edges_from_vertex = edges_from_vertex->next;
		}
		i++;
	}
}

t_list	**build_graph(t_lemin *lemin)
{
	int		vertices;
	char	**connections_matrix;
	t_list	**graph;
	int		i;

	vertices = lemin->map_size;
	connections_matrix = lemin->pipes;
	graph = ft_memalloc(sizeof(t_list*) * (vertices + 1));
	i = 0;
	while (i < vertices)
	{
		add_connections_to_graph(&graph[i], i, connections_matrix[i]);
		i++;
	}
	hook_up_rev_edges(graph, vertices);
	return (graph);
}

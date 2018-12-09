/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:46:50 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/09 13:01:20 by tboissel         ###   ########.fr       */
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

static void			add_connections_to_graph(t_list **vertex, \
int vtx_nb, char *links)
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

static void			hook_up_rev_edges(t_list **graph, int vertices)
{
	t_list	*e_f_v;
	t_list	*e_to_up;
	int		i;
	int		cur_edge_t;

	i = 0;
	while (i < vertices)
	{
		e_f_v = graph[i];
		while (e_f_v)
		{
			if (((t_edge*)(e_f_v->content))->rev == NULL)
			{
				cur_edge_t = ((t_edge*)(e_f_v->content))->sink;
				e_to_up = graph[cur_edge_t];
				while (((t_edge*)(e_to_up->content))->sink != i)
					e_to_up = e_to_up->next;
				((t_edge*)e_to_up->content)->rev = (t_edge*)e_f_v->content;
				((t_edge*)e_f_v->content)->rev = (t_edge*)e_to_up->content;
			}
			e_f_v = e_f_v->next;
		}
		i++;
	}
}

t_listarray			build_graph(t_lemin *lemin)
{
	int			vertices;
	char		**connections_matrix;
	t_listarray	graph;
	int			i;

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

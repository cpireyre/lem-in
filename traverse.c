/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:14:33 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/25 09:47:51 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	link_path(t_list **graph, t_edge *edge, int sink)
{
	t_list	*destination_vertex;
	t_edge	*cur_edge;

	destination_vertex = graph[edge->sink];
	cur_edge = (t_edge*)(destination_vertex->content);
	while (destination_vertex != graph[sink])
	{
		while (cur_edge->flow != 1 && destination_vertex)
		{
			destination_vertex = destination_vertex->next;
			if (destination_vertex)
				cur_edge = (t_edge*)(destination_vertex->content);
		}
		if (destination_vertex)
		{
			if (DEBUG)
				ft_printf("\t\tHooked up %d->%d and %d->%d.\n", edge->source, edge->sink, cur_edge->source, cur_edge->sink);
			cur_edge->previous = edge;
			edge->next = cur_edge;
		}
		edge = cur_edge;
		destination_vertex = graph[edge->sink];
		cur_edge = (t_edge*)(destination_vertex->content);
	}
}

void		link_graph(t_list ***graph, int source, int sink)
{
	t_list	*edges_from_start;
	t_edge	*edge;

	edges_from_start = (*graph)[source];
	if (DEBUG)
		ft_printf("DEBUG: Linking graph edges...\n");
	while (edges_from_start)
	{
		edge = (t_edge*)edges_from_start->content;
		if (edge->flow == 1)
		{
			if (DEBUG)
				ft_printf("\tPath from %d through %d.\n", source, edge->sink);
			link_path(*graph, edge, sink);
		}
		edges_from_start = edges_from_start->next;
	}
}

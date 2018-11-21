/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:01:30 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/21 15:13:49 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "graph.h"

int		shortest_path_length(t_list ***graph, int source, int sink, int size)
{
	int		len;
	t_list	*vertex;
	t_edge	**first_path;
	t_edge	*edge;

	first_path = breadth_first_search(*graph, source, sink, size);
	edge = first_path[sink];
	while (edge->source != source)
	{
		edge->flow += 1;
		edge->rev->flow -= 1;
		edge = first_path[edge->source];
	}
	edge->flow += 1;
	edge->rev->flow -= 1;
	if (!first_path)
		return (0);
	len = 0;
	vertex = (*graph)[source];
	while (vertex != (*graph)[sink])
	{
		len++;
		vertex = (*graph)[next_vertex_id(vertex)];
	}
	free(first_path);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:01:30 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/05 14:59:57 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clear_dumb_paths(t_sender *sender, t_list *start, int flow)
{
	int		i;

	i = 0;
	while (i < flow)
	{
		if (!sender->ants_to_send[i] && ((t_edge*)(start->content))->flow)
		{
			if (DEBUG)
				ft_printf("DEBUG: Path %d (of flow %d) is being cleared out.", \
					   	i, ((t_edge*)(start->content))->flow);
			((t_edge*)(start->content))->flow = 0;
		}
		i++;
		start = start->next;
	}
}

int		shortest_path_length(t_list ***graph, int source, int sink, int size)
{
	int		len;
	t_edge	**first_path;
	t_edge	*edge;

	first_path = breadth_first_search(*graph, source, sink, size);
	if (!first_path)
		return (0);
	edge = first_path[sink];
	while (edge->source != source)
	{
		edge->flow += 1;
		edge->rev->flow -= 1;
		edge = first_path[edge->source];
	}
	edge->flow += 1;
	edge->rev->flow -= 1;
	len = count_path_length(*graph, source, sink);
	free(first_path);
	return (len);
}

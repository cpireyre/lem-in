/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:50:59 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/20 10:10:39 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "graph.h"

char	*ft_find_room_name(t_lemin *lemin, int room_nb)
{
	t_rooms *tmp_rooms;

	tmp_rooms = lemin->rooms;
	while (room_nb--)
		tmp_rooms = tmp_rooms->next;
	return (tmp_rooms->name);
}

int	next_vertex_id(t_list *vertex)
{
	t_edge	*edge;

	edge = (t_edge*)(vertex->content);
	while (edge->flow != 1)
	{
		vertex = vertex->next;
		edge = (t_edge*)(vertex->content);
	}
	return (edge->sink);
}

void	send_one_ant(t_list **graph, int start, int end, t_lemin *lemin)
{
	int		nvi;
	int		lines;
	t_list	*vertex;

	nvi = start;
	if (DEBUG)
		ft_printf("DEBUG: Walking solution path...\n");
	vertex = graph[start];
	lines = 1;
	while (nvi != end)
	{
			nvi = next_vertex_id(vertex);
			if (DEBUG)
				ft_printf("(DEBUG: %d)\t", lines++);
			ft_printf("L1-%s\n", ft_find_room_name(lemin, nvi));
			vertex = graph[nvi];
	}
}

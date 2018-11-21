/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:50:59 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/21 10:06:03 by cpireyre         ###   ########.fr       */
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

int		next_vertex_id(t_list *vertex)
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

t_bool	send_one_ant(t_list *vertex, int start, int end, t_lemin *lemin, int i, t_sender *sender)
{
	int		lines;
	int		nvi;

	// if (DEBUG)
	// 	ft_printf("DEBUG: Walking solution path...\n");
	lines = 1;
	(void)start;
	// if (sender->ants_position[i] == start)
	// {
	// 	nvi = start;
	// 	sender->ants_sent++;
	// }
	nvi = next_vertex_id(vertex);
	// if (DEBUG)
	// 	ft_printf("(DEBUG: %d)\t", lines++);
	ft_printf("L%d-%s ", i + 1, ft_find_room_name(lemin, nvi));
	sender->ants_position[i] = nvi;
	if (nvi == end)
		return (true);
	else
		return (false);
}

void	send_ants(t_list **graph, int start, int end, t_lemin *lemin)
{
	int			i;
	t_sender	*sender;
	int			nvi;

	sender = ft_memalloc(sizeof(t_sender));
	sender->ants_position = ft_memalloc(sizeof(int) * lemin->ants);
	i = -1;
	while (++i < lemin->ants)
		sender->ants_position[i] = start;
	nvi = start;
	i = 1;
	sender->ants_sent = 0;
	sender->ants_arrived = 0;
	while (sender->ants_arrived < lemin->ants)
	{
		if (sender->ants_sent < lemin->ants)
			sender->ants_sent++;
		i = sender->ants_arrived - 1;
		while (++i < sender->ants_sent)
		{
			sender->ants_arrived += send_one_ant(graph[sender->ants_position[i]], start, end, lemin, i, sender);
		}
		ft_printf("\n");
	}
}

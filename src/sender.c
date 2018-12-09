/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:50:59 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/09 15:09:19 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				calculate_real_flow(t_sender *sender, int flow)
{
	int	i;
	int res;

	res = 0;
	i = -1;
	while (++i < flow)
	{
		if (sender->ants_to_send[i] > 0)
			res++;
	}
	return (res);
}

char			*ft_find_room_name(t_lemin *lemin, int room_nb)
{
	t_rooms *tmp_rooms;

	tmp_rooms = lemin->rooms;
	while (room_nb--)
		tmp_rooms = tmp_rooms->next;
	return (tmp_rooms->name);
}

int				next_vertex_id(t_list *vertex)
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

static t_bool	send_one_ant(t_list *vtx, t_lemin *lmn, int i, t_sender *sendr)
{
	int		nvi;
	t_bool	on_start;

	on_start = (sendr->ants_position[i] == lmn->start_id);
	if (lmn->flow > 1 && on_start)
		nvi = next_trajectory(sendr);
	else
		nvi = next_vertex_id(vtx);
	print_ant(i, ft_find_room_name(lmn, nvi), \
			sendr->ants_sent, lmn->ant_display);
	sendr->ants_position[i] = nvi;
	if (nvi == lmn->end_id)
		return (true);
	else
		return (false);
}

void			send_ants(t_listarray graph, t_lemin *lemin)
{
	int			i;
	t_sender	sender;

	init_sender(&sender, lemin, graph);
	i = -1;
	while (++i < lemin->ants)
		sender.ants_position[i] = lemin->start_id;
	while (sender.ants_arrived < lemin->ants)
	{
		if (sender.ants_sent < lemin->ants)
			sender.ants_sent += sender.real_flow;
		i = 0;
		while (i < sender.ants_sent && i < lemin->ants)
		{
			clear_dumb_paths(&sender, (graph)[lemin->start_id], lemin->flow);
			if (sender.ants_position[i] != lemin->end_id)
				sender.ants_arrived += send_one_ant(\
						graph[sender.ants_position[i]], lemin, i, &sender);
			i++;
		}
		ft_putchar('\n');
		if (DEBUG > 1)
			print_paths_info(&sender, lemin->flow);
	}
	free_sender(&sender);
}

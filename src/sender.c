/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:50:59 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/05 12:29:30 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		calculate_real_flow(t_sender *sender, int flow)
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

static t_bool	send_one_ant(t_list *vertex, t_lemin *lemin, int i, t_sender *sender)
{
	int		nvi;
	t_bool	on_start;

	on_start = (sender->ants_position[i] == lemin->start_id);
	if (lemin->flow > 1 && on_start)
		nvi = next_trajectory(sender);
	else
		nvi = next_vertex_id(vertex);
	print_ant(i, ft_find_room_name(lemin, nvi), sender->ants_sent, lemin->ant_display);
	sender->ants_position[i] = nvi;
	if (nvi == lemin->end_id)
		return (true);
	else
		return (false);
}

void	send_ants(t_list **graph, t_lemin *lemin)
{
	int			i;
	t_sender	sender;

	ft_bzero(&sender, sizeof(t_sender));
	sender.ants_position = ft_memalloc(sizeof(int) * (lemin->ants));
	sender.path_lengths = size_paths(graph, lemin);
	sender.shortest = ft_array_min(sender.path_lengths, lemin->flow);
	sender.ants_to_send = ft_memalloc(sizeof(int) * lemin->flow);
	how_many_ants_to_send(lemin, &sender);	
	clear_dumb_paths(&sender, (graph)[lemin->start_id], lemin->flow);
	sender.queue = queue_paths(&sender, graph[lemin->start_id], lemin->flow);

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
				sender.ants_arrived += send_one_ant(graph[sender.ants_position[i]], lemin, i, &sender);
			i++;
		}
		ft_putchar('\n');
		if (DEBUG)
			print_paths_info(&sender, lemin->flow);
	}
	free(sender.ants_to_send);
	free(sender.path_lengths);
	ft_lstdel(&sender.queue, &ft_free_node);
	free(sender.ants_position);
}
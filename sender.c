/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:50:59 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/24 13:32:26 by tboissel         ###   ########.fr       */
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

t_bool	send_one_ant(t_list *vertex, t_lemin *lemin, int i, t_sender *sender)
{
	int		nvi;
	t_list	*tmp;
	int		skipped_paths;

	tmp = vertex;
	t_bool on_start = (sender->ants_position[i] == lemin->start_id);
	if (lemin->flow > 1 && on_start)
	{
			if (sender->switch_path == 0)
			{
					nvi = next_vertex_id(vertex);
					sender->switch_path = 1;
			}
			else
			{
					skipped_paths = 0;
					while (tmp && skipped_paths < sender->switch_path)
					{
							tmp = tmp->next;
							if (tmp && ((t_edge*)(tmp->content))->flow == 1)
									skipped_paths++;
					}
					if (!tmp)
					{
							sender->switch_path = 1;
							nvi = next_vertex_id(vertex);
					}
					else
					{
							nvi = ((t_edge*)(tmp->content))->sink;
							sender->switch_path += 1;
					}
			}
	}
	else
			nvi = next_vertex_id(vertex);
	ft_printf("L%d-%s", i + 1, ft_find_room_name(lemin, nvi));
	(i + 1 == sender->ants_sent) ? 0 : ft_putchar(' ');
	sender->ants_position[i] = nvi;
	if (nvi == lemin->end_id)
		return (true);
	else
		return (false);
}

void	how_many_ants_to_send(t_lemin *lemin, t_sender *sender)
{
	int	average;
	int	ants_remaining;
	int	i;
	int	ants_average;

	ants_average = lemin->ants / lemin->flow;
	i = -1;
	average = 0;
	ants_remaining = lemin->ants;
	while (++i < lemin->flow)
		average += sender->path_lengths[i];
	average /= lemin->flow;
	i = -1;
	while (++i < lemin->flow)
	{
		sender->ants_to_send[i] = ants_average - (sender->path_lengths[i] - average);
		ft_printf("Path %d is %d rooms long, we'll send %d ants\n", i, sender->path_lengths[i], sender->ants_to_send[i]);
		if (sender->ants_to_send[i] < 0)
		{
			sender->ants_to_send[i] = 0;
			lemin->flow--;
		}
		ants_remaining -= sender->ants_to_send[i];
	}
	if (DEBUG)
	{
		i = -1;
		while (++i < lemin->flow)
			ft_printf("In path %d, we need to send %d ants\n", i, sender->ants_to_send[i]);
	}
}

void	send_ants(t_list **graph, t_lemin *lemin)
{
	int			i;
	t_sender	sender;

	sender.ants_position = ft_memalloc(sizeof(int) * (lemin->ants));
	sender.path_lengths = size_paths(graph, lemin);
	sender.shortest = ft_array_min(sender.path_lengths, lemin->flow);
	sender.ants_to_send = ft_memalloc(sizeof(int) * lemin->flow);
	how_many_ants_to_send(lemin, &sender);
	i = -1;
	while (++i < lemin->ants)
		sender.ants_position[i] = lemin->start_id;
	sender.ants_sent = 0;
	sender.ants_arrived = 0;
	sender.switch_path = 0;
	while (sender.ants_arrived < lemin->ants)
	{
		if (sender.ants_sent < lemin->ants)
				sender.ants_sent += lemin->flow;
		i = 0;
		while (i < sender.ants_sent && i < lemin->ants)
		{
				if (sender.ants_position[i] != lemin->end_id)
						sender.ants_arrived += send_one_ant(graph[sender.ants_position[i]], lemin, i, &sender);
				i++;
		}
		ft_putchar('\n');
	}
	free(sender.path_lengths);
	free(sender.ants_position);
}

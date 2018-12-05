/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:20:41 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/05 14:52:54 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*size_paths(t_list **graph, t_lemin *lemin)
{
	int		*app;
	int		i;
	t_list	*edges_from_start;
	t_edge	*edge;

	if (DEBUG > 2)
		ft_printf("DEBUG: Computing number of ants to send per path.\n");
	app = ft_memalloc(sizeof(int) * lemin->flow);
	i = 0;
	edges_from_start = graph[lemin->start_id];
	while (i < lemin->flow)
	{
		edge = (t_edge*)edges_from_start->content;
		if (edge->flow == 1)
		{
			app[i] = count_path_length(graph, edge->sink, lemin->end_id);
			if (DEBUG > 1)
				ft_printf("\tPath %d is %d edges long.\n", i, app[i]);
			i++;
		}
		edges_from_start = edges_from_start->next;
	}
	return (app);
}

void	how_many_ants_to_send(t_lemin *lemin, t_sender *sender)
{
	int	avg;
	int	ants_remaining;
	int	i;
	int	ants_avg;

	ants_avg = lemin->ants / lemin->flow;
	i = -1;
	avg = 0;
	ants_remaining = lemin->ants;
	while (++i < lemin->flow)
		avg += sender->path_lengths[i];
	avg /= lemin->flow;
	i = -1;
	while (++i < lemin->flow)
	{
		sender->ants_to_send[i] = ants_avg - (sender->path_lengths[i] - avg);
		if (sender->ants_to_send[i] < 0)
			sender->ants_to_send[i] = 0;
		ants_remaining -= sender->ants_to_send[i];
	}
	if (ants_remaining < 0)
		ants_remaining = too_many_ants_sent(lemin, sender, -ants_remaining);
	i = -1;
	if (ants_remaining)
		ants_remaining = repart_extra_ants(lemin, sender, avg, ants_remaining);
}

int		too_many_ants_sent(t_lemin *lemin, t_sender *sender, int to_subtract)
{
	int	i;

	while (to_subtract > 0)
	{
		i = -1;
		while (++i < lemin->flow)
		{
			if (sender->ants_to_send[i] > 0)
			{
				sender->ants_to_send[i]--;
				to_subtract--;
			}
		}
	}
	return (-to_subtract);
}

int		repart_extra_ants(t_lemin *lemin, t_sender *sender, int avg, int to_add)
{
	int	i;

	if (lemin->ants == 1)
	{
		i = -1;
		while (++i < lemin->flow)
			if (sender->shortest == sender->path_lengths[i])
			{
				sender->ants_to_send[i] = 1;
				return (1);
			}
	} 
	while (to_add > 0)
	{
		i = -1;
		while (++i < lemin->flow)
		{
			if (sender->ants_to_send[i] > 0 && sender->path_lengths[i] <= avg)
			{
				sender->ants_to_send[i]++;
				// sender->path_lengths[i]++;
				to_add--;
				if (DEBUG > 2)
					ft_printf("DEBUG: to_add = %d", to_add);
				if (to_add == 0)
					break ;
			}
		}
	}
	return (0);
}

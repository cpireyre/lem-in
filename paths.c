/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:20:41 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/25 13:18:57 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool	reset_sender(int *ats, int to_skip, int flow)
{
	int	i;

	i = to_skip - 1;
	while (++i < flow)
	{
		if (ats[i] != 0)
			return (false);
	}
	return (true);
}

int		get_optimal_path(t_sender *sender, t_list *starting_edges, int flow)
{
	int		skipping;
	t_edge	*edge;

	if (reset_sender(sender->ants_to_send, sender->to_skip, flow))
		sender->to_skip = 0;
	skipping = 0;
	edge = ((t_edge*)(starting_edges->content));
	while (skipping < sender->to_skip)
	{
		edge = ((t_edge*)(starting_edges->content));
		if (((edge->flow > 0 && sender->ants_to_send[skipping] == 0)) || sender->ants_to_send[skipping])
			skipping++;
		starting_edges = starting_edges->next;
	}
	edge = ((t_edge*)(starting_edges->content));
	while (edge->flow != 1)
	{
		edge = ((t_edge*)(starting_edges->content));
		starting_edges = starting_edges->next;
	}
	sender->to_skip++;
	sender->ants_to_send[skipping] -= 1;
	if (sender->ants_to_send[skipping] == 0)
		sender->real_flow--;
	return (edge->sink);
}

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
		if (edge->flow > 0)
		{
			app[i] = count_path_length(graph, edge->sink, lemin->end_id);
			if (DEBUG > 1)
				ft_printf("\tPath %d is %d edges long.\n", i, app[i]);
			i++;
		}
		edges_from_start = edges_from_start->next;
	}
	if (DEBUG > 2)
		ft_printf("\tShortest path appears to be %d edges long.\n", ft_array_min(app, lemin->flow));
	return (app);
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
		if (sender->ants_to_send[i] < 0)
			sender->ants_to_send[i] = 0;
		ants_remaining -= sender->ants_to_send[i];
	}
	if (ants_remaining < 0)
		ants_remaining = too_many_ants_sent(lemin, sender, -ants_remaining);
	if (DEBUG > 2)
		ft_printf("DEBUG: %d remaining ants, supposedly.\n", ants_remaining);
	i = -1;
	if (ants_remaining)
		ants_remaining = repart_extra_ants(lemin, sender, average, ants_remaining);
	sender->real_flow = calculate_real_flow(sender, lemin->flow);
}

int		too_many_ants_sent(t_lemin *lemin, t_sender *sender, int ants_to_subtract)
{
	int	i;

	while (ants_to_subtract > 0)
	{
		i = -1;
		while (++i < lemin->flow)
		{
			if (sender->ants_to_send[i] > 0)
			{
				sender->ants_to_send[i]--;
				ants_to_subtract--;
			}
		}
	}
	return (-ants_to_subtract);
}

int		repart_extra_ants(t_lemin *lemin, t_sender *sender, int average, int ants_to_add)
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
	while (ants_to_add > 0)
	{
		i = -1;
		while (++i < lemin->flow)
		{
			if (sender->ants_to_send[i] > 0 && sender->path_lengths[i] <= average)
			{
				sender->ants_to_send[i]++;
				ants_to_add--;
				if (DEBUG > 2)
					ft_printf("DEBUG: ants_to_add = %d", ants_to_add);
				if (ants_to_add == 0)
					break ;
			}
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:20:41 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/06 18:25:01 by cpireyre         ###   ########.fr       */
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
			if (DEBUG > 1)
				ft_printf("DEBUG: Path %d (of flow %d) cleared out.\n", \
					   	i, ((t_edge*)(start->content))->flow);
			((t_edge*)(start->content))->flow = 0;
		}
		i++;
		start = start->next;
	}
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

void	how_many_redux(t_list *lengths, int ants)
{
	int		count;

	count = ft_lstdepth(lengths);
	(void)ants;
	if (DEBUG)
		ft_printf("DEBUG: %d paths.\n", count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:20:41 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/18 10:34:32 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		ants_remaining = repart_extra_ants(lemin, sender, ants_remaining);
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

t_bool	case_one_ant(t_lemin *lemin, t_sender *sender)
{
	int	i;

	i = -1;
	while (++i < lemin->flow)
		if (sender->shortest == sender->path_lengths[i])
		{
			sender->ants_to_send[i] = 1;
			return (true);
		}
	return (false);
}

int		get_nb_lines(t_sender *sender, t_lemin *lemin)
{
	int	ret;
	int	i;

	i = -1;
	ret = 0;
	while (++i < lemin->flow)
	{
		ret = sender->path_lengths[i] + sender->ants_to_send[i] > ret ? \
sender->path_lengths[i] + sender->ants_to_send[i] : ret;
	}
	return (ret);
}

int		repart_extra_ants(t_lemin *lemin, t_sender *sender, int to_add)
{
	int	i;
	int	lines;

	if (lemin->ants == 1)
		if (case_one_ant(lemin, sender))
			return (0);
	while (to_add > 0)
	{
		lines = get_nb_lines(sender, lemin);
		i = -1;
		while (++i < lemin->flow)
		{
			if (sender->path_lengths[i] + sender->ants_to_send[i] <= lines)
			{
				sender->ants_to_send[i]++;
				to_add--;
				if (to_add == 0)
					break ;
			}
		}
	}
	return (0);
}

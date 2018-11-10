/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 07:55:45 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/10 16:17:32 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_size_list(t_rooms *rooms)
{
	int	i;

	i = 0;
	while (rooms && ++i)
		rooms = rooms->next;
	return (i);
}

int		count_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int			debug_size_list(t_paths *paths)
{
	int res;

	res = 0;
	while (paths)
	{
		paths = paths->next;
		res++;
	}
	return (res);
}

int			get_end_links(t_lemin *lemin)
{
	int		i;
	int		j;
	int		res;

	res = 0;
	j = -1;
	i = 0;
	while (lemin->pipes[i][i])
	{
		if (lemin->pipes[i][i] == END)
			break ;
		i++;
	}
	while (++j < lemin->map_size)
		if (lemin->pipes[i][j] == CONNECTED)
			res++;
	if (DEBUG)
		ft_printf("DEBUG: end_links = %d\n", res);
	return (res);
}

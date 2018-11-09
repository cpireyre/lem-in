/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:50:20 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/09 17:09:38 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool		algo(t_lemin *lemin)
{
	if (!(lemin->end_links = get_end_links(lemin)))
		return (false);
	create_first_path(lemin);
	scout(lemin);
	return (true);
}

void		create_following_path(t_paths **path, t_lemin *lemin)
{
	t_paths	*new;

	printf("Create following\n");
	new = ft_memalloc(sizeof(t_paths));
	new->scout = ft_memalloc((lemin->map_size + 1) * sizeof(int));
	ft_memset(new->scout, -1, sizeof(int) * (lemin->map_size));
	ft_memcpy(new->scout, (*path)->scout, lemin->map_size * sizeof(int));
	new->prev = (*path);
	new->next = NULL;
	(*path)->next = new;
}

int	debug_size_list(t_paths *paths)
{
	int res = 0;

	while (paths)
	{
		paths = paths->next;
		res++;
	}
	return (res);
}

t_bool		scout(t_lemin *lemin)
{
	int		separations;
	int		i;
	
		separations = ft_get_nb_separations(lemin);
		i = separations;
		while (separations-- != 1)
		{
			create_following_path(&lemin->paths, lemin);
			lemin->paths = lemin->paths->next;
		}
		separations = -1;
		while (lemin->paths->prev)
			lemin->paths = lemin->paths->prev;
		while (++separations < i)
		{
			scout_progress(lemin, separations);
			if (lemin->paths->next)
				lemin->paths = lemin->paths->next;	
			print_paths(lemin->paths, lemin->map_size);
		}
	return (false);
}

void	scout_progress(t_lemin *lemin, int separation)
{
	int	i;
	int	j;
	int	row;

	ft_printf("APPEL separation = %d\n", separation);
	j = 0;
	row = 0;
	i = -1;
	while (lemin->paths->scout[++i] != -1)
		ft_printf("val = %d\n", lemin->paths->scout[i]);
	row = lemin->paths->scout[i - 1];
	while (j < lemin->map_size)
	{
		if (lemin->pipes[row][j] == CONNECTED)
		{
			ft_printf("scout[i] = %d\n", lemin->paths->scout[i]);
			lemin->paths->scout[i] = j;
			separation--;
		}
		if (separation == -1)
			return;
		j++;
	}
}

int			ft_get_nb_separations(t_lemin *lemin)
{
	int		i;
	int		row;
	int		res;

	res = 0;
	i = 0;
	while (lemin->paths->scout[i + 1] != -1)
		i++;
	row = lemin->paths->scout[i];
	i = -1;
	while (++i < lemin->map_size)
	{
		printf("i = %d   row = %i\n", i, row);
		if (lemin->pipes[i][row] == CONNECTED)
			res++;
	}
	if (DEBUG)
		ft_printf("nb_separations %d = %d\n", lemin->paths->scout[i], res);
	return (res);
}

void		create_first_path(t_lemin *lemin)
{
	int		i;
	
	i = 0;
	while (lemin->pipes[i][i] != START)
		i++;
	lemin->paths = ft_memalloc(sizeof(t_paths));
	lemin->paths->scout = ft_memalloc(sizeof(int) * (lemin->map_size + 1));
	ft_memset(lemin->paths->scout, -1, sizeof(int) * (lemin->map_size));
	lemin->visited_rooms = ft_memalloc(sizeof(int) * lemin->map_size);
	lemin->paths->scout[0] = i;
	lemin->visited_rooms[0] = i;
	lemin->paths->prev = NULL;
	if (DEBUG)
		ft_printf("scout[0] = %d\n", lemin->paths->scout[0]);
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
			break;
		i++;
	}
	while (++j < lemin->map_size)
	{
		printf("pipes = %d\n", lemin->pipes[i][j]);
		if (lemin->pipes[i][j] == CONNECTED)
			res++;
	}
	if (DEBUG)
		printf("end_links = %d\n", res);
	return (res);
}

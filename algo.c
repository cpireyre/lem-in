/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:50:20 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/09 12:48:03 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool		algo(t_lemin *lemin)
{
	if (!(lemin->end_links = get_end_links(lemin)))
		return (false);
	create_first_path(lemin);
	//while (something)
		(scout(lemin));
	return (true);
}

void		create_following_path(t_paths **path)
{
	t_paths	*new;

	printf("Create following\n");
	new = ft_memalloc(sizeof(t_paths));
	new->scout = ft_memalloc(sizeof((*path)->scout));
	ft_memcpy(new, (*path)->scout, sizeof((*path)->scout));
	new->prev = (*path);
	new->next = NULL;
	(*path)->next = new;
}

t_bool		scout(t_lemin *lemin)
{
	int		separations;
	t_paths *tmp;
	int		i;

	tmp = lemin->paths;
//	while (tmp)
//	{
		separations = ft_get_nb_separations(lemin);
		i = separations;
		while (separations--)
			create_following_path(&tmp);
		tmp = tmp->next;
		while (separations++ < i - 1)
			scout_progress(lemin, separations);
		printf("lemin->paths->scout[0] = %d   lemin->paths->scout[1] = %d\n", lemin->paths->scout[0], lemin->paths->scout[1]);
//	}
	return (false);
}

void	scout_progress(t_lemin *lemin, int separation)
{
	int	i;
	int	j;
	int	row;

	i = 0;
	j = 0;
	row = 0;
	while (lemin->paths->scout[i++])
		;
	i--;
	row = lemin->paths->scout[i - 1];
	while (j < lemin->map_size)
	{
		if (lemin->pipes[j][row] == CONNECTED)
		{	
			lemin->paths->scout[i] = j;
			separation--;
		}
		if (separation == 0)
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
	while (lemin->paths->scout[i + 1])
		i++;
	row = lemin->paths->scout[i];
	i = -1;
	while (++i < lemin->map_size)
		if (lemin->pipes[i][row] == CONNECTED)
			res++;
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

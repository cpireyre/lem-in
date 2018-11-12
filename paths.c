/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 16:16:19 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/10 18:03:18 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		pluck_path(t_paths **path)
{
	t_paths	*tmp;

	tmp = (*path)->prev;
	if ((*path)->next)
		(*path)->next = (*path)->next->next;
	if ((*path)->prev)
		(*path)->prev = (*path)->prev->prev;
	free((*path)->scout);
	free(*path);
	(*path) = tmp;
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
	ft_memset(lemin->visited_rooms, -1, sizeof(int) * (lemin->map_size));
	lemin->paths->scout[0] = i;
	lemin->visited_rooms[0] = i;
	lemin->paths->prev = NULL;
	if (DEBUG)
		ft_printf("DEBUG: scout[0] = %d\n", lemin->paths->scout[0]);
}

void		insert_path(t_paths **current, t_lemin *lemin)
{
	t_paths		*new;
	t_paths		*old_next;

	old_next = (*current)->next;
	if (old_next)
	{
		if (DEBUG)
			ft_printf("DEBUG: current path has no next.\n");
		return ;
	}
	new = ft_memalloc(sizeof(t_paths));
	new->scout = ft_memalloc((lemin->map_size + 1) * sizeof(int));
	ft_memset(new->scout, -1, sizeof(int) * (lemin->map_size));
	ft_memcpy(new->scout, (*current)->scout, lemin->map_size * sizeof(int));
	new->prev = (*current);
	new->next = old_next;
}

void		create_following_path(t_paths **path, t_lemin *lemin)
{
	t_paths	*new;

	if (DEBUG)
		ft_printf("DEBUG: Updating path.\n");
	if ((*path)->next)
		insert_path(path, lemin);
	else
	{
		new = ft_memalloc(sizeof(t_paths));
		new->scout = ft_memalloc((lemin->map_size + 1) * sizeof(int));
		ft_memset(new->scout, -1, sizeof(int) * (lemin->map_size));
		ft_memcpy(new->scout, (*path)->scout, sizeof(int) * lemin->map_size);
		new->prev = (*path);
		new->next = NULL;
		(*path)->next = new;
	}
}

void		add_room_visited_list(t_lemin *lemin, int i)
{
	int		j;

	j = 0;
	while (lemin->visited_rooms[j] != -1)
		j++;
	lemin->visited_rooms[j] = lemin->paths->scout[i];
}

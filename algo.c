/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:50:20 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/10 17:28:26 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** t_bool		algo(t_lemin *lemin)
** {
** 	if (!(lemin->end_links = get_end_links(lemin)))
** 		return (false);
** 	create_first_path(lemin);
** 	scout(lemin);
** 	scout(lemin);
** 	scout(lemin);
** 	scout(lemin);
** 	return (true);
** }
*/

t_bool		bfs(t_lemin *lemin)
{
	int	i;
	t_rooms	*ptr;
	int	*ignore;
	t_paths	*path_tmp;

	i = 0;
	ptr = lemin->rooms;
	ignore = ft_memalloc(sizeof(int) * lemin->map_size);
	path_tmp = NULL;
	while (ptr)
	{
		if (DEBUG)
		{
			ft_printf("DEBUG: \"%s\" is connected to...\n", ptr->name);
			print_adjacent_rooms(lemin->pipes, i);
		}
		lemin->paths = ft_memalloc(sizeof(t_paths));
		if (path_tmp)
			lemin->paths->prev = path_tmp;
		else
			lemin->paths->prev = NULL;
		lemin->paths->scout = store_following_rooms(lemin->pipes, i, ignore);
		if (DEBUG)
			print_paths(lemin->paths, lemin->map_size);
		ignore[i] = 1;
		i++;
		ptr = ptr->next;
		path_tmp = lemin->paths;
		lemin->paths = lemin->paths->next;
	}
	return (true);
}

t_bool		scout(t_lemin *lemin)
{
	int		separations;
	int		i;

	separations = ft_get_nb_separations(lemin);
	i = separations;
	if (DEBUG)
		ft_printf("DEBUG: separations = %d\n", i);
	while (separations-- > -1)
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

void		scout_progress(t_lemin *lemin, int separation)
{
	int	i;
	int	j;
	int	row;

	j = 0;
	row = 0;
	i = -1;
	while (lemin->paths->scout[++i] != -1)
		;
	row = lemin->paths->scout[i - 1];
	while (j < lemin->map_size)
	{
		if (lemin->pipes[row][j] == CONNECTED)
		{
			lemin->paths->scout[i] = j;
			separation--;
		}
		if (separation == -1)
		{
			add_room_visited_list(lemin, i);
			return ;
		}
		j++;
	}
}

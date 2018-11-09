/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:04:50 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/09 10:18:57 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** store pipes:
** roomsize = sizelist (lemin->rooms)
** malloc lemin->pipes tab[roomsize][roomsize]
** remplir diagonale avec les types
** tant qu'on a le format x-y
** Verifier que x et y sont des noms salles e
*/

void	fill_diagonal_types(t_lemin *lemin)
{
	t_rooms	*tmp;
	int		i;

	tmp = lemin->rooms;
	i = 0;
	while (lemin->rooms)
	{
		lemin->pipes[i][i] = lemin->rooms->type;
		i++;
		lemin->rooms = lemin->rooms->next;
	}
	lemin->rooms = tmp;
}

int		find_name_list(char *name, t_rooms *rooms)
{
	int	i;

	i = 0;
	while (rooms)
	{
		if (!ft_strcmp(rooms->name, name))
			return (i);
		i++;
		rooms = rooms->next;
	}
	return (-1);
}

void	fill_tab_pipes(t_lemin *lemin, t_list **ptr)
{
	int		first_room_place;
	int		second_room_place;
	char	**split;

	while (*ptr)
	{
		split = ft_strsplit((char *)(*ptr)->content, '-');
		if (count_split(split) != 2)
		{
			free_split(split);
			return ;
		}
		first_room_place = find_name_list(split[0], lemin->rooms);
		if (first_room_place != -1)
			second_room_place = find_name_list(split[1], lemin->rooms);
		if (first_room_place == -1 || second_room_place == -1)
		{
			free_split(split);
			return ;
		}
		lemin->pipes[first_room_place][second_room_place] = CONNECTED;
		lemin->pipes[second_room_place][first_room_place] = CONNECTED;
		*ptr = (*ptr)->next;
		free_split(split);
	}
}

void	store_pipes(t_list **ptr, t_lemin *lemin)
{
	int	nb_rooms;
	int	i;

	i = -1;
	nb_rooms = ft_size_list(lemin->rooms);
	lemin->pipes = ft_memalloc(sizeof(char*) * (nb_rooms + 1));
	while (++i < nb_rooms)
		lemin->pipes[i] = ft_memalloc(sizeof(char) * (nb_rooms + 1));
	lemin->map_size = nb_rooms;
	fill_diagonal_types(lemin);
	fill_tab_pipes(lemin, ptr);
}

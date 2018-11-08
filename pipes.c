/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:04:50 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/08 15:43:13 by cpireyre         ###   ########.fr       */
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

int		ft_size_list(t_rooms *rooms)
{
	int	i;

	i = 0;
	while (rooms && ++i)
		rooms = rooms->next;
	return (i);
}

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
		first_room_place = find_name_list(split[0], lemin->rooms);
		second_room_place = find_name_list(split[1], lemin->rooms);
//		if (split && split[0] && split[1] && !split[2])
//		{
			lemin->pipes[first_room_place][second_room_place] = CONNECTED;
			lemin->pipes[second_room_place][first_room_place] = CONNECTED;
//		}
//		free_split(split);
		*ptr = (*ptr)->next;
	}
}

void	store_pipes(t_list **ptr, t_lemin *lemin)
{
	int	nb_rooms;
	int	i;

	i = -1;
	nb_rooms = ft_size_list(lemin->rooms);
	lemin->pipes = ft_memalloc(sizeof(int*) * nb_rooms);
	while (++i < nb_rooms)
		lemin->pipes[i] = ft_memalloc(sizeof(int) * nb_rooms);
	fill_diagonal_types(lemin);
	fill_tab_pipes(lemin, ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:04:50 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/25 09:31:18 by cpireyre         ###   ########.fr       */
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

static void				fill_diagonal_types(t_lemin *lemin)
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

static int				find_name_list(char *name, t_rooms *rooms)
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

static inline t_bool	is_dash(char to_check)
{
	return (to_check == '-');
}

int						ft_strcountif(const char *str, t_bool (*check)(char))
{
	int		count;

	count = 0;
	while (*str)
	{
		count += check(*str);
		str++;
	}
	return (count);
}

static inline t_bool	parse_pipes(t_list **ptr, char ***split, t_lemin *lemin)
{
	int		rooms_to_connect[2];

	if (ft_strcountif(((char*)(*ptr)->content), &is_dash) > 1 || count_split(*split) != 2)
	{
		free_split(*split);
		*ptr = (*ptr)->next;
		return (false);
	}
	rooms_to_connect[0] = find_name_list(*split[0], lemin->rooms);
	if (rooms_to_connect[0] != -1)
		rooms_to_connect[1] = find_name_list((*split)[1], lemin->rooms);
	if (rooms_to_connect[0] == -1 || rooms_to_connect[1] == -1)
	{
		free_split(*split);
		return (false);
	}
	lemin->pipes[rooms_to_connect[0]][rooms_to_connect[1]] = CONNECTED;
	lemin->pipes[rooms_to_connect[1]][rooms_to_connect[0]] = CONNECTED;
	return (true);
}

static void				fill_tab_pipes(t_lemin *lemin, t_list **ptr)
{
	char	**split;

	while (*ptr)
	{
		if (((char*)(*ptr)->content)[0] == '#')
		{
			(*ptr) = (*ptr)->next;
			continue ;
		}
		split = ft_strsplit((char *)(*ptr)->content, '-');
		if (!parse_pipes(ptr, &split, lemin))
			break ;
		*ptr = (*ptr)->next;
		free_split(split);
	}
}

static int				get_special_id(char **matrix, int to_find)
{
	int		i;

	i = 0;
	while (matrix[i][i] != to_find)
		i++;
	return (i);
}

t_bool					store_pipes(t_list **ptr, t_lemin *lemin)
{
	int		nb_rooms;
	int		i;
	t_bool	has_one_pipe;

	i = -1;
	has_one_pipe = false;
	nb_rooms = ft_size_list(lemin->rooms);
	lemin->pipes = ft_memalloc(sizeof(char*) * (nb_rooms + 1));
	while (++i < nb_rooms)
	{
		lemin->pipes[i] = ft_memalloc(sizeof(char) * (nb_rooms + 1));
		ft_memset(lemin->pipes[i], NORMAL, sizeof(char) * (nb_rooms));
	}
	lemin->map_size = nb_rooms;
	fill_diagonal_types(lemin);
	fill_tab_pipes(lemin, ptr);
	lemin->start_id = get_special_id(lemin->pipes, START);
	lemin->end_id = get_special_id(lemin->pipes, END);
	while (--i >= 0 && !has_one_pipe)
		if (!has_one_pipe)
			has_one_pipe = !(!ft_strchr(lemin->pipes[i], CONNECTED));
	return (has_one_pipe);
}

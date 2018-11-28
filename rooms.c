/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 08:06:24 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/28 13:24:17 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool	check_room_coordinate(char **name)
{
	while (ft_isdigit(**name))
		(*name)--;
	if (**name == '-' || **name == '+')
		(*name)--;
	(*name)++;
	if (!ft_isint(*name))
		return (false);
	(*name)--;
	if (**name != ' ')
		return (false);
	return (true);
}

t_bool	room_is_valid(char *name)
{
	if (name[0] == 'L' || name[0] == '#')
		return (false);
	name += ft_strlen(name) - 1;
	if (!check_room_coordinate(&name))
		return (false);
	name--;
	if (!check_room_coordinate(&name))
		return (false);
	return (true);
}

t_rooms	*new_room(char *name_ptr, t_byte type, t_coord *coord, t_lemin *lemin)
{
	t_rooms	*new;

	new = ft_memalloc(sizeof(t_rooms));
	new->coord = ft_memalloc(sizeof(t_coord));
	new->coord->x = coord->x;
	new->coord->y = coord->y;
	new->name = name_ptr;
	new->type = type;
	if (type == START)
		new->ant_nb = lemin->ants;
	else
		new->ant_nb = 0;
	new->next = NULL;
	return (new);
}

char	*get_room_name(char *input)
{
	size_t	i;
	char	*name;

	i = ft_strlen(input);
	if (room_is_valid(input))
	{
		while (!ft_isspace(input[i]))
			i--;
		i--;
		while (!ft_isspace(input[i]))
			i--;
		name = ft_strnew(i);
		name = ft_strncpy(name, input, i);
		if (ft_strchr(name, '-'))
		{
			ft_strdel(&name);
			return (NULL);
		}
		else
			return (name);
	}
	else
		return (NULL);
}

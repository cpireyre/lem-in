/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:07:17 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/28 13:21:33 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Add room:
** creer un maillon t_rooms avec:
** type = type;
** name = room_line - 2 derniers blocs
** return (false) si nom commence par L
** Verifier qu'un nom n'est pas deja used par un autre maillon,
**  return(false) sinon
** return (true) quand on trouve line type x-y et rien derriere;
*/

t_bool				store_ants(t_list **head, t_lemin *lemin)
{
	while (((char*)(*head)->content)[0] == '#')
	{
		if (ft_strequ((char*)(*head)->content, "##start")
				|| ft_strequ((char*)(*head)->content, "##end"))
			return (false);
		(*head) = (*head)->next;
	}
	if (ft_isint((char*)(*head)->content))
	{
		lemin->ants = ft_atoi((char*)(*head)->content);
		if (DEBUG > 1)
			ft_printf("DEBUG: Stored %d ant%c.\n", lemin->ants, \
					lemin->ants > 1 ? 's' : 0);
		if (lemin->ants >= 0)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

t_bool				room_already_exists(t_rooms *map, char *room)
{
	while (map)
	{
		if (!ft_strcmp(map->name, room))
		{
			if (DEBUG > 1)
				ft_printf("DEBUG: \"%s\" already exists.\n", room);
			return (true);
		}
		map = map->next;
	}
	return (false);
}

t_coord				get_coord(char *input)
{
	int				i;
	char			**splitted;
	t_coord			coord;

	coord.x = 0;
	coord.y = 0;
	splitted = ft_strsplit(input, ' ');
	i = 0;
	while (splitted[i++])
		;
	if (i > 3)
	{
		coord.x = ft_atoi(splitted[i - 3]);
		coord.y = ft_atoi(splitted[i - 2]);
	}
	return (coord);
}

t_bool				add_room(t_lemin **lemin, char *input, t_byte type)
{
	t_rooms *new;
	char	*room_name;
	t_coord coord;

	coord = get_coord(input);
	room_name = get_room_name(input);
	if (type == START || type == END)
		if (!store_special_rooms(*lemin, room_name, type))
			return (false);
	if (!room_name)
	{
		if (DEBUG > 1)
			ft_printf("DEBUG: \"%s\" invalid somehow.\n", input);
		ft_strdel(&room_name);
		return (false);
	}
	if ((*lemin)->rooms && room_already_exists((*lemin)->rooms, room_name))
	{
		ft_strdel(&room_name);
		return (false);
	}
	new = new_room(room_name, type, &coord, *lemin);
	new->next = (*lemin)->rooms;
	(*lemin)->rooms = new;
	return (true);
}

t_bool				store_special_rooms(t_lemin *lemin, char *name, t_byte type)
{
	if (type == END)
	{
		if (lemin->end_name)
		{
			free(name);
			return (false);
		}
		lemin->end_name = ft_strdup(name);
	}
	else if (type == START)
	{
		if (lemin->start_name)
		{
			free(name);
			return (false);
		}
		lemin->start_name = ft_strdup(name);
	}
	return (true);
}

static inline void	parse_special(t_list **ptr, t_byte *type, char **str)
{
	if (!ft_strcmp(*str, "##start"))
		*type = START;
	else if (!ft_strcmp(*str, "##end"))
		*type = END;
	(*ptr) = (*ptr)->next;
	*str = (char*)((*ptr)->content);
	while (*str[0] == '#')
	{
		(*ptr) = (*ptr)->next;
		*str = (char*)((*ptr)->content);
	}
}

void				store_rooms(t_list **ptr, t_lemin *lemin)
{
	t_byte	type;
	char	*str;

	while (*ptr)
	{
		str = (char*)((*ptr)->content);
		if (!*str)
			return ;
		type = NORMAL;
		if (str[0] == '#')
		{
			if (str[1] != '#')
			{
				(*ptr) = (*ptr)->next;
				continue ;
			}
			else
				parse_special(ptr, &type, &str);
		}
		if (add_room(&lemin, str, type) == false)
			return ;
		(*ptr) = (*ptr)->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:07:17 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/25 15:56:08 by cpireyre         ###   ########.fr       */
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

static t_bool				add_room(t_lemin **lemin, char *input, t_byte type)
{
	t_rooms *new;
	char	*room_name;

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
	new = new_room(room_name, type);
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
			ft_memdel((void**)&name);
			return (false);
		}
		lemin->end_name = ft_strdup(name);
	}
	else if (type == START)
	{
		if (lemin->start_name)
		{
			ft_memdel((void**)&name);
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

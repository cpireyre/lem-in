/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:07:17 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/08 15:31:24 by cpireyre         ###   ########.fr       */
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

t_bool	store_ants(t_list **head, t_lemin *lemin)
{
	t_list	*ptr;

	ptr = *head;
	if (ft_isint((char*)ptr->content))
	{
		lemin->ants = ft_atoi((char*)ptr->content);
		if (DEBUG)
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

t_bool	room_already_exists(t_rooms *map, char *room)
{
	while (map)
	{
		if (!ft_strcmp(map->name, room))
		{
			if (DEBUG)
				ft_printf("\"%s\" already exists.\n", room);
			return (true);
		}
		map = map->next;
	}
	return (false);
}

t_bool	add_room(t_rooms **map, char *input, t_byte type)
{
	t_rooms *new;
	char	*room_name;

	room_name = get_room_name(input);
	if (!room_name)
	{
		ft_strdel(&room_name);
		return (false);
	}
	if (*map && room_already_exists((*map), room_name))
		return (false);
	new = new_room(room_name, type);
	new->next = *map;
	*map = new;
	return (true);
}

void	store_rooms(t_list **ptr, t_lemin *lemin)
{
	t_byte type;

	while ((*ptr))
	{
		type = NORMAL;
		if (((char *)((*ptr)->content))[0] == '#')
		{
			if (((char *)((*ptr)->content))[1] != '#')
			{
				(*ptr) = (*ptr)->next;
				continue ;
			}
			else
			{
				if (!ft_strcmp((char*)((*ptr)->content), "##start"))
					type = START;
				else if (!ft_strcmp((char*)((*ptr)->content), "##end"))
					type = END;
				(*ptr) = (*ptr)->next;
			}
		}
		if (add_room(&lemin->rooms, (char *)((*ptr)->content), type) == false)
			return ;
		(*ptr) = (*ptr)->next;
	}
}

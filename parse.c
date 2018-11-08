/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:07:17 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/08 11:44:13 by cpireyre         ###   ########.fr       */
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
			ft_printf("DEBUG: Stored %d ants.\n", lemin->ants);
		return (true);
	}
	else
		return (false);
}

t_bool	room_already_exists(t_rooms *map, char *room)
{
	map = map->next;
	while (map)
	{
		if (map->name == room)
			return (true);
		map = map->next;
		if (DEBUG)
			ft_printf("\"%s\" already exists.\n", room);
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

/*
** TODO:
** add_room(lemin->rooms, (char *)ptr->content, type);
*/

/*
** t_bool		store_rooms(t_list **head, t_lemin *lemin)
** {
** 	t_list *ptr;
** 	t_byte type;
**
** 	ptr = *head;
** 	while (ptr)
** 	{
** 		type = NORMAL;
** 		if (((char *)(ptr->content))[0] == '#')
** 		{
** 			if (((char *)(ptr->content))[1] != '#')
** 			{
** 				ptr = ptr->next;
** 				continue;
** 			}
** 			else
** 			{
** 				if (ft_strcmp((char*)(ptr->content), "##start"))
** 					type = START;
** 				else if (ft_strcmp((char*)(ptr->content), "##end"))
** 					type = END;
** 				ptr = ptr->next;
** 			}
** 		}
** 	}
** }
*/

/*
** store pipes:
** roomsize = sizelist (lemin->rooms)
** malloc lemin->pipes tab[roomsize][roomsize]
** remplir diagonale avec les types
** tant qu'on a le format x-y
** Verifier que x et y sont des noms salles e
*/

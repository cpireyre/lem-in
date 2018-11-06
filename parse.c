/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:07:17 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/06 16:13:53 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Add room:
** creer un maillon t_rooms avec:
** typeroom = type;
** room_name = room_line - 2 derniers blocs
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
		return (true);
	}
	else
		return (false);
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

void	print_list(t_list **head)
{
	t_list	*ptr;

	ptr = *head;
	while (ptr)
	{
		ft_putendl((char*)ptr->content);
		ptr = ptr->next;
	}
}

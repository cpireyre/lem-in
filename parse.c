/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:07:17 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/05 18:09:16 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem-in.h"

t_bool		store_ants(t_list **head, t_lemin *lemin)
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

t_bool		store_rooms(t_list **head, t_lemin *lemin)
{
	t_list *ptr;
	t_byte type;

	ptr = *head;
	while (ptr)
	{
		type = NORMAL;
		if (((char *)(ptr->content))[0] == '#')
			if (((char *)(ptr->content))[1] != '#')
			{
				ptr = ptr->next;
				continue;
			}
			else
			{
				if (ft_strcmp((char*)(ptr->content), "##start"))
					type = START;
				else if (ft_strcmp((char*)(ptr->content), "##end"))
					type = END;
				ptr = ptr->next;
			}
		add_room(lemin->rooms, (char *)ptr->content, type);
	}
	store_pipes(lemin, ptr);
}

void	store_pipes(t_lemin *lemin, t_list *ptr)
{
	//roomsize = sizelist (lemin->rooms)
	//malloc lemin->pipes tab[roomsize][roomsize]
	//remplir diagonale avec les types

	//tant qu'on a le format x-y
	//Verifier que x et y sont des noms salles e
} 

t_bool	add_room(t_rooms *rooms, char *room_line, t_byte type)
{
	//creer un maillon t_rooms avec:
	// typeroom = type;
	// room_name = room_line - 2 derniers blocs
	// return (false) si nom commence par L
	//Verifier qu'un nom n'est pas deja used par un autre maillon, return(false) sinon
	// return (true) quand on trouve line type x-y et rien derriere;
}

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

int		main(void)
{
	t_list		*arg;
	char		*line;
	t_lemin		lemin;

	line = NULL;
	while (ft_gnl(0, &line))
		ft_lstappend(&arg, ft_lstnew(line, sizeof(char) * (ft_strlen(line) + 1)));
	if (!(arg))
		ft_exit("empty list\n");
	if (!(store_ants(&arg, &lemin)))
		ft_exit("Not a number of ants\n");
	arg = arg->next;
	if (!(store_rooms(&arg, &lemin)))
		ft_exit("Error in room definition\n");
	ft_putendl("initial check(s) done. printing list now:");
	print_list(&arg);
	return (0);
}

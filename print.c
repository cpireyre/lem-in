/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:20:47 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/10 16:10:12 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_node_string(t_list *node)
{
	ft_putendl((char*)node->content);
}

void	print_rooms(t_rooms *map)
{
	int		i;
	char	*room_type;

	i = -1;
	if (DEBUG)
		ft_putendl("DEBUG: Printing rooms.");
	while (map)
	{
		if (map->type == END)
			room_type = "END";
		else if (map->type == START)
			room_type = "START";
		else
			room_type = "NORMAL";
		if (DEBUG)
			ft_putstr("DEBUG: ");
		ft_printf("\tRoom %d: \"%s\", type %s.\n", ++i, map->name, room_type);
		map = map->next;
	}
}

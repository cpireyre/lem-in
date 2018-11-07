/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:20:47 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/07 08:22:43 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	print_rooms(t_rooms	*map)
{
	int		i;

	i = -1;
	while (map)
	{
		ft_printf("Room %d: %s, type %hhu.\n", ++i, map->room_name, map->type_room);
		map = map->next;
	}
}

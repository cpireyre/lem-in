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

void	print_paths(t_paths *path, int len)
{
	t_paths	*tmp;

	ft_putendl("DEBUG: Printing paths.");
	tmp = NULL;
	while (path)
	{
		ft_print_int_tab(path->scout, len);
		tmp = path;
		path = path->next;
	}
	path = tmp;
	ft_putendl("DEBUG: And backwards:");
	while (path)
	{
		ft_print_int_tab(path->scout, len);
		path = path->prev;
	}
	ft_putendl("DEBUG: Done printing paths.");
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

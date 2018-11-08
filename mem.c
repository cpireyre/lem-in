/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:42:13 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/08 10:26:05 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_list(t_list **head)
{
	t_list	*tmp;
	t_list	*ptr;

	ptr = *head;
	while (ptr)
	{
		tmp = ptr->next;
		ft_strdel((char**)&ptr->content);
		free(ptr);
		ptr = tmp;
	}
}

void	free_rooms(t_rooms **head)
{
	t_rooms	*tmp;
	t_rooms	*ptr;

	ptr = *head;
	while (ptr)
	{
		tmp = ptr->next;
		if (DEBUG)
			ft_printf("DEBUG: Freeing room \"%s\".\n", (char*)ptr->name);
		ft_strdel((char**)&ptr->name);
		free(ptr);
		ptr = tmp;
	}
}
	
void	free_lemin(t_lemin *addr)
{
	free_rooms(&(addr)->rooms);
	free(addr);
}

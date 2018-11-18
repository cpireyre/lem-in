/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:42:13 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/10 16:10:52 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_string(void *string, size_t size)
{
	(void)size;
	ft_strdel((char**)&string);
}

void	free_rooms(t_rooms **head)
{
	t_rooms	*tmp;
	t_rooms	*ptr;

	ptr = *head;
	while (ptr)
	{
		tmp = ptr->next;
		ft_strdel((char**)&ptr->name);
		free(ptr);
		ptr = tmp;
	}
}

void	free_split(char **split)
{
	char	**tmp;
	char	**ptr;

	if (!split)
		return ;
	tmp = split;
	ptr = split;
	while (*split)
	{
		tmp = split + 1;
		ft_strdel(split);
		split = tmp;
	}
	free(ptr);
}

void	free_node(void *ptr, size_t size)
{
	free(ptr);
	(void)size;
}

void	free_lemin(t_lemin *addr)
{
	free(addr->start_name);
	free(addr->end_name);
	free_rooms(&(addr)->rooms);
	free_split(addr->pipes);
	free(addr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:42:13 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/09 09:48:46 by tboissel         ###   ########.fr       */
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

void	free_lemin(t_lemin *addr)
{
	free(addr->start_name);
	free(addr->end_name);
	free_rooms(&(addr)->rooms);
	free_split(addr->pipes);
	free(addr);
}

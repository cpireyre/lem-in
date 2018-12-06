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

void	free_rooms(t_rooms **head)
{
	t_rooms	*tmp;
	t_rooms	*ptr;

	ptr = *head;
	while (ptr)
	{
		tmp = ptr->next;
		ft_strdel((char**)&ptr->name);
		ft_memdel((void**)&ptr);
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
	ft_memdel((void**)&ptr);
}

void	free_lemin(t_lemin *addr)
{
	ft_memdel((void**)&addr->start_name);
	ft_memdel((void**)&addr->end_name);
	free_rooms(&(addr)->rooms);
	free_split(addr->pipes);
}

void	free_graph(t_list **graph, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (graph[i])
			ft_lstdel(&graph[i], &ft_free_node);
		i++;
	}
	ft_memdel((void**)&graph);
}

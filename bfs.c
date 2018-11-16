/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:46:55 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/16 16:52:43 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	make_one_list(char *connections, t_list **current_room)
{
	int	i;

	i = 0;
	while (connections[i])
	{
		if (connections[i] == CONNECTED)
			ft_lstappend(current_room, ft_lstnew(&i, sizeof(int)));
		i++;
	}
}

t_list	**build_adjacency_list(t_lemin *lemin)
{
	t_list	**adjacency_list;
	t_list	**ptr;
	int		i;

	adjacency_list = ft_memalloc(sizeof(t_list*) * (lemin->map_size + 1));
	ptr = adjacency_list;
	i = 0;
	while (lemin->pipes[i])
	{
		make_one_list(lemin->pipes[i], &adjacency_list[i]);
		i++;
	}
	return (ptr);
}

void	print_int_node(t_list *ptr)
{
	ft_printf("\t...room %d.\n", *(int*)(ptr->content));
}

void	print_adjacency_list(t_list **list)
{
	t_list	*ptr;
	int		i;

	i = 0;
	while (list[i])
	{
		ptr = list[i];
		ft_printf("DEBUG: Printing children of room %d:\n", i);
		ft_lstiter(ptr, &print_int_node);
		i++;
	}
}

void	free_adjacent(void *ptr, size_t size)
{
	if (DEBUG)
		ft_printf("\t\t...freeing room %d.\n", *(int*)ptr);
	free(ptr);
	(void)size;
}

void	free_adjacency_list(t_list **list, int size)
{
	int	i;

	i = 0;
	if (DEBUG)
		ft_putendl("DEBUG: Freeing adjacency list:");
	while (i < size)
	{
		if (list[i])
		{
			if (DEBUG)
				ft_printf("\tFreeing list %d...\n", i);
			ft_lstdel(&list[i], &free_adjacent);
		}
		i++;
	}
	free(list);
}

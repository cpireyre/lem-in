/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:50:20 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/10 17:28:26 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_start_id(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i][i] != START)
		i++;
	return (i);
}

t_bool	is_queued(t_list *queue, int room)
{
	while (queue)
	{
		if (*(int*)queue->content == room)
			return (true);
		queue = queue->next;
	}
	return (false);
}

void	bfs_process_queue(t_list **queue, t_list **adjacency_list, 
				t_bool **visited_addr, t_tree **solution)
{
	t_list	*adjacent_rooms;
	int		room_to_visit;
	int		current_room;
	t_list	*tmp;

	if (!DEBUG)
			(void)solution;
	if (!queue || !*queue)
		return ;
	room_to_visit = *(int*)(*queue)->content;
	adjacent_rooms = adjacency_list[room_to_visit];
	while (adjacent_rooms)
	{
		current_room = *(int*)adjacent_rooms->content;
		if (!is_queued(*queue, current_room)
				&& (*visited_addr)[current_room] == false)
		{
			ft_lstappend(queue, ft_lstnew(&current_room, sizeof(int)));
			if (DEBUG)
				ft_printf("\t\tEnqueued room %d.\n", current_room);
		}
		adjacent_rooms = adjacent_rooms->next;
	}
	(*visited_addr)[room_to_visit] = true;
	tmp = (*queue)->next;
	if (DEBUG)
		ft_printf("\tDone visiting room %d...\n", room_to_visit);
	ft_lstdelone(queue, &free_adjacent);
	*queue = tmp;
}

t_bool	bfs(t_lemin *lemin)
{
	t_list	**adjacency_list;
	t_list	*queue;
	t_bool	*visited_rooms;
	int		start_id;
	t_tree	*solution;

	adjacency_list = build_adjacency_list(lemin);
	visited_rooms = ft_memalloc(sizeof(t_bool) * lemin->map_size);
	start_id = get_start_id(lemin->pipes);
	queue = ft_lstnew(&start_id, sizeof(int));
	visited_rooms[start_id] = true;
	solution = ft_tree_new(&start_id, sizeof(int));
	if (DEBUG)
		ft_putendl("DEBUG: ---> Commencing breadth-first search! <---");
	while (queue)
		bfs_process_queue(&queue, adjacency_list, &visited_rooms, &solution);
	ft_tree_free(&solution);
	free_adjacency_list(adjacency_list);
	free(visited_rooms);
	return (true);
}

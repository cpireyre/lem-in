/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trajectory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:00:19 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/05 15:23:58 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*enqueue_paths(t_sender *sender, t_list *start_vtx, int flow)
{
	t_list			*queue;
	int				i;
	t_trajectory	trajectory;

	i = 0;
	queue = NULL;
	while (1)
	{
		while (i < flow && sender->ants_to_send[i] == 0)
			i++;
		while (start_vtx && ((t_edge*)(start_vtx)->content)->flow == 0)
			start_vtx = start_vtx->next;
		if (i == flow || !start_vtx)
			break ;
		trajectory.direction = ((t_edge*)(start_vtx)->content);
		trajectory.sender_id = i;
		ft_lstappend(&queue, ft_lstnew(&trajectory, sizeof(t_trajectory)));
		if (DEBUG > 1)
				ft_printf("DEBUG: Queued path %d: %d->%d.\n", i, \
					   	((t_edge*)(start_vtx)->content)->source,\
					   	((t_edge*)(start_vtx)->content)->sink);
		i++;
		start_vtx = start_vtx->next;
	}
	return (queue);
}

int		next_trajectory(t_sender *sender)
{
	t_trajectory	elem;
	t_list			*ptr;

	ptr = sender->queue->next;
	ft_memcpy(&elem, sender->queue->content, sender->queue->content_size);
	ft_lstdelone(&sender->queue, &ft_free_node);
	sender->queue = ptr;
	if (sender->ants_to_send[elem.sender_id] > 0)
	{
		sender->ants_to_send[elem.sender_id]--;
		ft_lstappend(&sender->queue, ft_lstnew(&elem, sizeof(t_trajectory)));
		if (DEBUG > 1)
			ft_printf("DEBUG: Sending ant to vertex %d. Queued it again.\n", \
				   	elem.direction->sink);
	}
	else
		sender->real_flow--;
	return (elem.direction->sink);
}

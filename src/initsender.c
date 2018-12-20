/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initsender.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:23:51 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/18 10:30:40 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_sender(t_sender *sender, t_lemin *lemin, t_list **graph)
{
	ft_bzero(sender, sizeof(t_sender));
	sender->ants_position = ft_memalloc(sizeof(int) * (lemin->ants));
	sender->path_lengths = size_paths(graph, lemin);
	sender->shortest = ft_array_min(sender->path_lengths, lemin->flow);
	sender->ants_to_send = ft_memalloc(sizeof(int) * lemin->flow);
	how_many_ants_to_send(lemin, sender);
	sender->real_flow = calculate_real_flow(sender, lemin->flow);
	clear_dumb_paths(sender, (graph)[lemin->start_id], lemin->flow);
	sender->queue = enqueue_paths(sender, graph[lemin->start_id], lemin->flow);
}

void	free_sender(t_sender *sender)
{
	ft_memdel((void**)&sender->ants_to_send);
	ft_memdel((void**)&sender->path_lengths);
	ft_lstdel(&sender->queue, &ft_free_node);
	ft_memdel((void**)&sender->ants_position);
}

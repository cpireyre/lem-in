/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 07:55:45 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/18 10:34:25 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_size_list(t_rooms *rooms)
{
	int	i;

	i = 0;
	while (rooms && ++i)
		rooms = rooms->next;
	return (i);
}

int		count_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int		count_path_length(t_listarray graph, int source, int sink)
{
	int		len;
	t_list	*vertex;

	len = 1;
	vertex = (graph)[source];
	while (vertex != (graph)[sink])
	{
		len++;
		vertex = (graph)[next_vertex_id(vertex)];
	}
	return (len);
}

int		*size_paths(t_listarray graph, t_lemin *lemin)
{
	int		*app;
	int		i;
	t_list	*edges_from_start;
	t_edge	*edge;

	if (DEBUG)
		ft_printf("DEBUG: Computing lengths of all paths.\n");
	app = ft_memalloc(sizeof(int) * lemin->flow);
	i = 0;
	edges_from_start = graph[lemin->start_id];
	while (i < lemin->flow)
	{
		edge = (t_edge*)edges_from_start->content;
		if (edge->flow == 1)
		{
			app[i] = count_path_length(graph, edge->sink, lemin->end_id);
			if (DEBUG)
				ft_printf("\tPath %d is %d edges long.\n", i, app[i]);
			i++;
		}
		edges_from_start = edges_from_start->next;
	}
	return (app);
}

void	clear_dumb_paths(t_sender *sender, t_list *start, int flow)
{
	int		i;

	i = 0;
	while (i < flow && start)
	{
		while (start && (((t_edge*)(start->content))->flow == 0))
			start = start->next;
		if (i == flow || !start)
			break ;
		if (!sender->ants_to_send[i] && ((t_edge*)(start->content))->flow)
		{
			if (DEBUG)
				ft_printf("DEBUG: Path %d (of flow %d) cleared out.\n", \
i, ((t_edge*)(start->content))->flow);
			((t_edge*)(start->content))->flow = 0;
		}
		i++;
		if (start->next)
			start = start->next;
	}
}

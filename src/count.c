/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 07:55:45 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/27 13:36:48 by tboissel         ###   ########.fr       */
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

int		count_path_length(t_list **graph, int source, int sink)
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

int		alternate_count(t_edge **path, int source, int sink)
{
	t_edge	*edge;
	int		len;

	len = 0;
	if (!path)
		return (-1);
	edge = path[sink];
	while (edge->source != source)
	{
		len++;
		edge = path[edge->source];
	}
	return (len);
}

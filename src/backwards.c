/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backwards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 12:55:55 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/09 12:56:04 by tboissel         ###   ########.fr       */
=======
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:15:53 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/14 16:16:33 by cpireyre         ###   ########.fr       */
>>>>>>> super
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		prev_vertex_id(t_list *vertex)
{
	t_edge	*edge;

	edge = ((t_edge*)(vertex->content))->rev;
	while (edge->flow != 1)
	{
		vertex = vertex->next;
		if (!vertex)
			return (-1);
		edge = ((t_edge*)(vertex->content))->rev;
	}
	return (edge->source);
}

int		count_back_length(t_listarray graph, int source, int sink)
{
	int		len;
	t_list	*vertex;

	len = 1;
	vertex = (graph)[source];
	while (source != sink)
	{
		len++;
		source = prev_vertex_id(vertex);
		if (source == -1)
			return (len);
		vertex = (graph)[source];
	}
	return (len);
}

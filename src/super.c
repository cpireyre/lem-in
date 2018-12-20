/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 13:11:59 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/17 17:51:27 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				flow_to_vertex(t_list *vertex)
{
	int		count;
	t_edge	*edge;

	count = 0;
	while (vertex)
	{
		edge = ((t_edge*)(vertex->content))->rev;
		if (DEBUG)
			ft_printf("\t...now looking at %d->%d. Flow %d.\n", edge->source, \
edge->sink, edge->flow);
		if (edge->flow == 1)
			count++;
		vertex = vertex->next;
	}
	return (count);
}

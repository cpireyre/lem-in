/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:19:03 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/14 16:19:04 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			printnode_edge(t_list *elem)
{
	print_edge((t_edge*)(elem->content));
}

void			flow_thru_edge(t_edge *edge)
{
	edge->flow += 1;
	edge->rev->flow -= 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:15:59 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/17 17:46:22 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int	expected_lines(int ants, int flow, int avg)
{
	return ((ants - 1) / flow + avg);
}

int					print_path_analysis(t_listarray graph, t_lemin *lemin)
{
	int		*lengths;
	int		avg_len;
	int		ret;

	lengths = size_paths(graph, lemin);
	avg_len = ft_tab_avg(lengths, lemin->flow);
	ret = expected_lines(lemin->ants, lemin->flow, avg_len);
	if (DEBUG)
	{
		ft_printf("DEBUG: Avg path length: %d.\n", avg_len);
		ft_printf("\tExpecting %d lines to solve.\n", ret);
	}
	ft_lstdel(&lemin->path_lengths, &ft_free_node);
	ft_memdel((void**)&lengths);
	return (ret);
}

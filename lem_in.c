/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:41:08 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/06 17:09:18 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_list		*arg;
	char		*l;
	t_lemin		*lemin;

	l = NULL;
	arg = NULL;
	lemin = ft_memalloc(sizeof(t_lemin));
	while (ft_gnl(0, &l))
		ft_lstappend(&arg, ft_lstnew(l, sizeof(char) * (ft_strlen(l) + 1)));
	if (!(arg))
		ft_printf("empty list\n");
	if (!(store_ants(&arg, lemin)))
		ft_printf("Invalid number of ants.\n");
	print_list(&arg);
	free_list(&arg);
	free(lemin);
	return (0);
}

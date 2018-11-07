/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:41:08 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/07 08:05:17 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	quit_lem_in(t_list **lst, t_lemin *env, const char *err, int status)
{
	free_list(lst);
	free_lemin(env);
	ft_exit(err, status);
}

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
		quit_lem_in(&arg, lemin, "No arguments.", EXIT_FAILURE);
	if (!(store_ants(&arg, lemin)))
		quit_lem_in(&arg, lemin, "Invalid number of ants.", EXIT_FAILURE);
	print_list(&arg);
	quit_lem_in(&arg, lemin, "", EXIT_SUCCESS);
}

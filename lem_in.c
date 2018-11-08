/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:41:08 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/08 15:00:50 by cpireyre         ###   ########.fr       */
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
	t_list		*usr_in;
	t_list		*ptr;
	char		*l;
	t_lemin		*lemin;

	l = NULL;
	usr_in = NULL;
	lemin = ft_memalloc(sizeof(t_lemin));
	lemin->rooms = NULL;
	while (ft_gnl(0, &l))
		ft_lstappend(&usr_in, ft_lstnew(l, sizeof(char) * (ft_strlen(l) + 1)));
	if (!(usr_in))
		quit_lem_in(&usr_in, lemin, "No arguments.", EXIT_FAILURE);
	ptr = usr_in->next;
	if (!(store_ants(&usr_in, lemin)))
		quit_lem_in(&usr_in, lemin, "Invalid number of ants.", EXIT_FAILURE);
	store_rooms(&ptr, lemin);
	print_rooms(lemin->rooms);
	store_pipes(&ptr, lemin);
	print_list(&usr_in);
	if (DEBUG)
		print_rooms(lemin->rooms);
	quit_lem_in(&usr_in, lemin, "", EXIT_SUCCESS);
}

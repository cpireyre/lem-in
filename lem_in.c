/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:41:08 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/10 17:09:13 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	quit_lem_in(t_list **lst, t_lemin *env, const char *err, int status)
{
	free_list(lst);
	free_lemin(env);
	ft_exit(err, status);
}

t_bool	map_has_in_out(t_lemin *lemin)
{
	if (DEBUG)
		ft_printf("DEBUG: Start room: \"%s\", end room: \"%s\".\n",
				lemin->start_name, lemin->end_name);
	return (lemin->start_name && lemin->end_name);
}

int		main(void)
{
	t_list		*usr_in;
	t_list		*ptr;
	t_list		*tmp;
	char		*l;
	t_lemin		*lemin;

	l = NULL;
	usr_in = NULL;
	lemin = ft_memalloc(sizeof(t_lemin));
	lemin->rooms = NULL;
	while (ft_gnl(0, &l))
	{
		if (!ft_isascii(l[0]))
			break ;
		ft_lstappend(&usr_in, ft_lstnew(l, sizeof(char) * (ft_strlen(l) + 1)));
	}
	tmp = usr_in;
	if (!(usr_in))
		quit_lem_in(&usr_in, lemin, "ERROR: No arguments.", EXIT_FAILURE);
	if (!(store_ants(&usr_in, lemin)))
		quit_lem_in(&usr_in, lemin, "ERROR: Invalid number of ants.", EXIT_FAILURE);
	ptr = usr_in->next;
	store_rooms(&ptr, lemin);
	if (!lemin->rooms || !map_has_in_out(lemin))
		quit_lem_in(&usr_in, lemin, "ERROR: Map is empty or lacks start or end room.", EXIT_FAILURE);
	print_rooms(lemin->rooms);
	if (DEBUG)
		ft_printf("DEBUG: All rooms are stored. Processing pipes.\n");
	store_pipes(&ptr, lemin);
	bfs(lemin);
	print_list(&usr_in);
	if (DEBUG)
		print_rooms(lemin->rooms);
	quit_lem_in(&tmp, lemin, "", EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:41:08 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/16 17:31:49 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "graph.h"

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
		ft_lstappend(&usr_in, ft_lstnew(l, sizeof(char) * (ft_strlen(l) + 1)));
	tmp = usr_in;
	if (!(usr_in))
		quit_lem_in(&tmp, lemin, "ERROR: No arguments.\n", EXIT_FAILURE);
	if (!(store_ants(&usr_in, lemin)))
		quit_lem_in(&tmp, lemin, "ERROR: Invalid number of ants.\n", EXIT_FAILURE);
	ptr = usr_in->next;
	store_rooms(&ptr, lemin);
	if (!lemin->rooms || !map_has_in_out(lemin))
		quit_lem_in(&tmp, lemin, "ERROR: Map error.\n", EXIT_FAILURE);
	if (DEBUG)
	{
		print_rooms(lemin->rooms);
		ft_printf("DEBUG: All rooms are stored. Processing pipes.\n");
	}
	if (!store_pipes(&ptr, lemin))
		quit_lem_in(&tmp, lemin, "ERROR: No pipes.\n", EXIT_FAILURE);
	t_list	**solution = build_graph(lemin);
	int	max_flow = edmonds_karp(&solution, lemin);
	print_list(&tmp);
	if (max_flow)
	{
			ft_putchar('\n');
			ft_printf("\t\tMax flow here is %d.\n", max_flow);
			send_one_ant(solution, get_start_id(lemin->pipes), get_end_id(lemin->pipes), lemin);
	}
	free_graph(solution, lemin->map_size);
	quit_lem_in(&tmp, lemin, "", EXIT_SUCCESS);
}

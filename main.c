/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 08:41:56 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/25 09:09:54 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "graph.h"

t_list	*stdin_to_list(void)
{
	t_list		*usr_in;
	char		*l;

	l = NULL;
	usr_in = NULL;
	while (ft_gnl(0, &l))
		ft_lstappend(&usr_in, ft_lstnew(l, sizeof(char) * (ft_strlen(l) + 1)));
	return (usr_in);
}

void	solve(t_lemin *lemin)
{
	t_list		**s;
	int			f;

	s = build_graph(lemin);
	f = shortest_path_length(&s, lemin->start_id, lemin->end_id, lemin->map_size);
	lemin->flow = (f > 0) ? 1 : 0;
	if (f > 0)
		lemin->flow = 1 + edmonds_karp(&s, lemin);
	if (f > 0)
	{
		ft_putchar('\n');
		link_graph(&s, lemin->start_id, lemin->end_id);
		send_ants(s, lemin);
	}
	else
		ft_putendl("ERROR");
	free_graph(s, lemin->map_size);
}

int		main(void)
{
	t_list		*usr_in;
	t_list		*tmp;
	t_lemin		lemin;

	ft_bzero(&lemin, sizeof(t_lemin));
	usr_in = stdin_to_list();
	tmp = usr_in;
	parse(&usr_in, &tmp, &lemin);
	buf_print_list(tmp);
	solve(&lemin);
	quit_lem_in(&tmp, &lemin, "", EXIT_SUCCESS);
}

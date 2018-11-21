/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 08:41:56 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/21 15:14:36 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "graph.h"

int		main(void)
{
	t_list		*usr_in;
	t_list		*tmp;
	t_lemin		*lemin;
	t_list		**s;
	int			f;

	lemin = ft_memalloc(sizeof(t_lemin));
	lemin->rooms = NULL;
	usr_in = stdin_to_list();
	tmp = usr_in;
	parse(&usr_in, &tmp, lemin);
	s = build_graph(lemin);
	if ((f = shortest_path_length(&s, lemin->start_id, lemin->end_id, lemin->map_size)) <= lemin->ants)
	{
		if (DEBUG)
			ft_printf("DEBUG: Clearly, %d <= %d, and nobody here is retarded.\n", f, lemin->ants);
		f = 1 + edmonds_karp(&s, lemin->start_id, lemin->end_id, lemin->map_size);
	}
	ft_lstiter(tmp, &print_node_string);
	link_graph(&s, lemin->start_id, lemin->end_id);
	if (f)
	{
		ft_putchar('\n');
		send_ants(s, lemin);
	}
	else
		ft_putendl("ERROR");
	free_graph(s, lemin->map_size);
	quit_lem_in(&tmp, lemin, "", EXIT_SUCCESS);
}

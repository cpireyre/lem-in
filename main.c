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
	f = edmonds_karp(&s, lemin->start_id, lemin->end_id, lemin->map_size);
	ft_lstiter(tmp, &print_node_string);
	if (f)
	{
			ft_putchar('\n');
			if (DEBUG)
					ft_printf("\t\tMax flow here is %d.\n", f);
			send_one_ant(s, lemin->start_id, lemin->end_id, lemin);
	}
	else
		ft_putendl("ERROR");
	link_graph(&s, lemin->start_id, lemin->end_id);
	free_graph(s, lemin->map_size);
	quit_lem_in(&tmp, lemin, "", EXIT_SUCCESS);
}

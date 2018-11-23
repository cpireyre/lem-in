#include "lem_in.h"

int		ft_array_min(int *array, int size)
{
		int		index;
		int		min;

		index = 0;
		min = array[0];
		while (++index < size)
				min = ft_min(min, array[index]);
		return (min);
}

int		*ants_per_path(t_list **graph, t_lemin *lemin)
{
		int		*app;
		int		i;
		t_list	*edges_from_start;
		t_edge	*edge;

		if (DEBUG)
				ft_printf("DEBUG: Computing number of ants to send per path.\n");
		app = ft_memalloc(sizeof(int) * lemin->flow);
		i = 0;
		edges_from_start = graph[lemin->start_id];
		while (i < lemin->flow)
		{
				edge = (t_edge*)edges_from_start->content;
				if (edge->flow > 0)
				{
						app[i] = count_path_length(graph, edge->sink, lemin->end_id);
						if (DEBUG)
								ft_printf("\tPath %d is %d edges long.\n", i, app[i]);
						i++;
				}
				edges_from_start = edges_from_start->next;
		}
		if (DEBUG)
				ft_printf("\tShortest path appears to be %d edges long.\n", ft_array_min(app, lemin->flow));
		return (app);
}

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

int		*size_paths(t_list **graph, t_lemin *lemin)
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

void	how_many_ants_to_send(t_lemin *lemin, t_sender *sender)
{
	int	average;
	int	ants_remaining;
	int	i;
	int	ants_average;

	ants_average = lemin->ants / lemin->flow;
	i = -1;
	average = 0;
	ants_remaining = lemin->ants;
	while (++i < lemin->flow)
		average += sender->path_lengths[i];
	average /= lemin->flow;
	i = -1;
	while (++i < lemin->flow)
	{
		sender->ants_to_send[i] = ants_average - (sender->path_lengths[i] - average);
		if (sender->ants_to_send[i] < 0)
			sender->ants_to_send[i] = 0;
		ants_remaining -= sender->ants_to_send[i];
	}
	if (ants_remaining < 0)
		ants_remaining = too_many_ants_sent(lemin, sender, -ants_remaining);
	i = -1;
	while (++i < lemin->flow)
		ft_printf("in path %d that is %d rooms lomg, we'll send %d ants\n", i, sender->path_lengths[i], sender->ants_to_send[i]);
	ft_printf("There are %d ants remaining\n", ants_remaining);
}

int		too_many_ants_sent(t_lemin *lemin, t_sender *sender, int ants_to_substract)
{
	int	i;

	while (ants_to_substract > 0)
	{
		i = -1;
		while (++i < lemin->flow)
		{
			if (sender->ants_to_send[i] > 0)
			{
				sender->ants_to_send[i]--;
				ants_to_substract--;
			}
		}		
	}
	return (-ants_to_substract);
}

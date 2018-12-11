#include "lem_in.h"

void	print_path_analysis(t_listarray graph, t_lemin *lemin, int flow)
{
	t_sender	sender;

	ft_bzero(&sender, sizeof(t_sender));
	sender.ants_position = ft_memalloc(sizeof(int) * (lemin->ants));
	sender.path_lengths = size_paths(graph, lemin);
	sender.shortest = ft_array_min(sender.path_lengths, lemin->flow);
	sender.ants_to_send = ft_memalloc(sizeof(int) * lemin->flow);
	how_many_ants_to_send(lemin, &sender);
	if (DEBUG)
		print_paths_info(&sender, flow);
	free_sender(&sender);
}

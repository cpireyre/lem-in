#include "lem_in.h"
#include "graph.h"

/*
**	t_list **graph = vertices
**	t_list *queue = vertices to be visited on each pass of the BFS
**	will need some t_edge *find_end(t_edge **path) or something later
*/

t_bool		edge_is_valid(t_edge *edge, t_edge **path, int source)
{
		if (!((path)[edge->sink]) && edge->sink != source && edge->flow < 1)
				return (true);
		else
				return (false);
}

void		bfs_step(t_edge ***path, t_list **queue, t_list **graph, int source)
{
	t_list	*current_vertex;
	t_edge	*edge;
	int		vertex_no;
	t_list	*tmp;

	vertex_no = *(int*)(*queue)->content;
	current_vertex = graph[vertex_no];
	if (DEBUG)
		ft_printf("\tVisiting vertex %d.\n", vertex_no);
	while (current_vertex)
	{
			edge = (t_edge*)current_vertex->content;
			if (edge_is_valid(edge, *path, source))
			{
					(*path)[edge->sink] = edge;
					ft_lstappend(queue, ft_lstnew(&edge->sink, sizeof(int)));
					if (DEBUG)
						ft_printf("\t\tEnqueued vertex %d,\n", edge->sink);
			}
			current_vertex = current_vertex->next;
	}
	tmp = (*queue)->next;
	ft_lstdelone(queue, &free_adjacent);
	*queue = tmp;
}

t_edge		**breadth_first_search(t_list **graph, int source, int sink, int size)
{
	t_edge	**path;
	t_list	*queue;

	path = ft_memalloc(sizeof(t_edge*) * size);
	queue = ft_lstnew(&source, sizeof(int));
	if (DEBUG)
		ft_putendl("DEBUG: Commencing breadth-first search.");
	while (queue)
		bfs_step(&path, &queue, graph, source); 
	if (DEBUG && path[sink])
		ft_printf("DEBUG: BFS done. path[sink] flows from %d to %d. ", path[sink]->source, path[sink]->sink);
	if (!path[sink])
	{
		free(path);
		return (NULL);
	}
	return (path);
}

t_list	**edmonds_karp(t_lemin *lemin)
{
	t_list	**max_flow_network;
	t_edge	**path;
	t_edge	*edge;
	int		source;
	int		sink;
	int		max_flow;

	max_flow_network = build_graph(lemin);
	source = get_start_id(lemin->pipes);
	sink = get_end_id(lemin->pipes);
	max_flow = 0;
	if (DEBUG)
		ft_printf("DEBUG: \t\tCommencing Edmonds-Karp.\n");
	while ((path = breadth_first_search(max_flow_network, source, sink, lemin->map_size)))
	{
		if (DEBUG)
			ft_printf("Updating residual network:\n");
		edge = path[sink];
		while (edge->source != source)
		{
			edge->flow += 1;
			edge->rev->flow -= 1;
			if (DEBUG)
				ft_printf("\tAdded flow between %d and %d.\n", edge->source, edge->sink);
			edge = path[edge->source];
		}
			edge->flow += 1;
			edge->rev->flow -= 1;
			if (DEBUG)
				ft_printf("\tAdded flow between %d and %d.\n", edge->source, edge->sink);
		max_flow += 1;
		free(path);
	}
	if (DEBUG)
			ft_printf("DEBUG: \t\tEdmonds-Karp is finished. Max flow in this network is %d. Motherfuckers.\n", max_flow);
	return (max_flow_network);
}

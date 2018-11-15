#ifndef GRAPH_H
# define GRAPH_H

typedef struct	s_edge
{
	int				flow;
	int				source;
	int				sink;
	struct s_edge	*rev;
}				t_edge;

void	fill_edge(t_edge *edge, int source, int sink);
void	add_connections_to_graph(t_list **vertex, int vertex_nbr, char *connections);
t_list	**build_graph(t_lemin *lemin);
void	free_edge(void *ptr, size_t size);
void	free_graph(t_list **graph, int size);

#endif

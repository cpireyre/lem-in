#include "lem_in.h"

void			printnode_edge(t_list *elem)
{
	print_edge((t_edge*)(elem->content));
}

void			flow_thru_edge(t_edge *edge)
{
	edge->flow += 1;
	edge->rev->flow -= 1;
}

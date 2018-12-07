/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:20:47 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/05 14:54:38 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		buf_print_list(t_list *node)
{
	t_buf	buffer;

	buffer.filedesc = 1;
	buffer.written = 0;
	buffer.pos = 0;
	while (node)
	{
		putstr_buf(&buffer, (char*)node->content);
		putc_buf(&buffer, '\n');
		node = node->next;
	}
	flush_buf(&buffer);
}

void		print_ant(int i, char *room_name, int ants_sent, char *display)
{
	ft_putstr(display);
	ft_putnbr(i + 1);
	ft_putchar('-');
	ft_putstr(room_name);
	(i + 1 == ants_sent) ? 0 : ft_putchar(' ');
	if (!ft_strequ(display,"L"))
			ft_putstr("\e[0m");
}

void		print_rooms(t_rooms *map)
{
	int		i;
	char	*room_type;

	i = -1;
	if (DEBUG > 3)
		ft_putendl("DEBUG: Printing rooms.");
	while (map)
	{
		if (map->type == END)
			room_type = "END";
		else if (map->type == START)
			room_type = "START";
		else
			room_type = "NORMAL";
		if (DEBUG > 3)
		{
			ft_putstr("DEBUG: ");
			ft_printf("\tRoom %d: \"%s\", type %s.\n", \
							++i, map->name, room_type);
		}
		map = map->next;
	}
}

void		print_paths_info(t_sender *sender, int flow)
{
	int i;

	if (DEBUG)
	{
		ft_printf("DEBUG: Printing paths information...\n");
		i =  -1;
		while (++i < flow)
			ft_printf("\tIn path %d of length %d, we'll send %d ants.\n", i, \
				   	sender->path_lengths[i], sender->ants_to_send[i]);
	}
}

void		print_edge(t_edge *edge)
{
	ft_printf("\tCurrent edge: %d->%d. Flow %d.\n", \
			edge->source, edge->sink, edge->flow);
}

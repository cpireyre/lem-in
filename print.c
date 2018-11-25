/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:20:47 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/25 08:00:19 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	buf_print_list(t_list *node)
{
	t_buf	buffer;

	buffer.pos = 0;
	buffer.filedesc = 1;
	buffer.written = 0;
	while (node)
	{
		putstr_buf(&buffer, (char*)node->content);
		putc_buf(&buffer, '\n');
		node = node->next;
	}
	flush_buf(&buffer);
}

void	print_ant(int i, char *room_name, int ants_sent)
{
	ft_putchar('L');
	ft_putnbr(i + 1);
	ft_putchar('-');
	ft_putstr(room_name);
	(i + 1 == ants_sent) ? 0 : ft_putchar(' ');
}

void	print_rooms(t_rooms *map)
{
	int		i;
	char	*room_type;

	i = -1;
	if (DEBUG)
		ft_putendl("DEBUG: Printing rooms.");
	while (map)
	{
		if (map->type == END)
			room_type = "END";
		else if (map->type == START)
			room_type = "START";
		else
			room_type = "NORMAL";
		if (DEBUG)
			ft_putstr("DEBUG: ");
		ft_printf("\tRoom %d: \"%s\", type %s.\n", ++i, map->name, room_type);
		map = map->next;
	}
}

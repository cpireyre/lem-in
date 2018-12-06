/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:20:47 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/06 14:00:18 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*stdin_to_list(void)
{
	t_list		*usr_in;
	char		*l;

	l = NULL;
	usr_in = NULL;
	while (ft_gnl(0, &l))
		ft_lstappend(&usr_in, ft_lstnew(l, sizeof(char) * (ft_strlen(l) + 1)));
	return (usr_in);
}

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

void	print_ant(int i, char *room_name, int ants_sent, char *display)
{
	ft_putstr(display);
	ft_putnbr(i + 1);
	ft_putchar('-');
	ft_putstr(room_name);
	(i + 1 == ants_sent) ? 0 : ft_putchar(' ');
	if (!ft_strequ(display,"L"))
			ft_putstr("\x1b[0m");
}

void	print_rooms(t_rooms *map)
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
			ft_printf("\tRoom %d: \"%s\", type %s.\n", ++i, map->name, room_type);
		}
		map = map->next;
	}
}

void	print_paths_info(t_sender *sender, int flow)
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

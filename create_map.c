/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:20:51 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/05 14:28:30 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <time.h>

int			rand_a_b(int a, int b)
{
	return (rand() % (b - a) + a);
}

void		ft_background(t_visu *visu)
{
	int		i;

	i = -1;
	while (++i < visu->mlx->w_width * visu->mlx->w_height)
		visu->mlx->img.data[i] = 0x89663E + rand_a_b(0, 5) * 0x0F0F0F;
}

void		ft_create_image(t_visu *visu)
{
	int		i;
	int		j;
	t_rooms	*rooms;

	rooms = visu->lemin->rooms;
	while (rooms)
	{
		i = 0;
		while (i++ < 60)
		{
			j = 0;
			while (j++ < 60)
			{
				if (rooms->coord.x + i + (rooms->coord.y + j) * \
visu->mlx->w_width > 0 && rooms->coord.x + i + \
(rooms->coord.y + j) * visu->mlx->w_width < 1920000)
					visu->mlx->img.data[rooms->coord.x + i + \
(rooms->coord.y + j) * visu->mlx->w_width] = rooms->ant_nb * 0xFFFFFF;
			}
		}
		rooms = rooms->next;
	}
	rooms = visu->lemin->rooms;
}

t_coord		get_coordinates_room(int room_nb, t_lemin *lemin)
{
	t_coord	coord;
	t_rooms *rooms;

	rooms = lemin->rooms;
	while (room_nb--)
		lemin->rooms = lemin->rooms->next;
	coord.x = lemin->rooms->coord.x + 30;
	coord.y = lemin->rooms->coord.y + 30;
	lemin->rooms = rooms;
	return (coord);
}

void		create_pipes(t_visu *visu)
{
	int		i;
	int		j;
	t_coord	coord1;
	t_coord	coord2;

	i = -1;
	while (++i < visu->lemin->map_size)
	{
		j = -1;
		while (++j < i)
		{
			if (visu->lemin->pipes[i][j] == CONNECTED)
			{
				coord1 = get_coordinates_room(i, visu->lemin);
				coord2 = get_coordinates_room(j, visu->lemin);
				ft_bresenham(coord1, coord2, visu);
			}
		}
	}
}

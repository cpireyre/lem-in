/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:20:51 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/09 12:39:17 by tboissel         ###   ########.fr       */
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
(rooms->coord.y + j) * visu->mlx->w_width] = \
((rooms->ant_nb * 0x000060) > 0x0000FF ? 0x0000FF : rooms->ant_nb * 0x000060);
			}
		}
		rooms = rooms->next;
	}
	rooms = visu->lemin->rooms;
}

void		draw_square(t_coord r1, t_coord r2, t_visu *visu, int color)
{
	int		i;
	int		j;
	t_coord center;
	int		pos;

	center.x = (r1.x + r2.x) / 2;
	center.y = (r1.y + r2.y) / 2;
	i = -5;
	while (++i < 5)
	{
		j = -5;
		while (++j < 5)
		{
			pos = center.x + i + (center.y + j) * visu->mlx->w_width;
			if (pos > 0 && pos < visu->mlx->w_height * visu->mlx->w_width)
				visu->mlx->img.data[center.x + i + (center.y + j) * \
visu->mlx->w_width] = color;
		}
	}
}

void		create_pipes(t_visu *visu)
{
	t_coord ij;
	t_coord	coord1;
	t_coord	coord2;

	ij.x = -1;
	while (++ij.x < visu->lemin->map_size)
	{
		ij.y = -1;
		while (++ij.y < ij.x)
		{
			if (visu->lemin->pipes[ij.x][ij.y] == CONNECTED)
			{
				inner_pipes(visu, &coord1, &coord2, ij);
				draw_square(coord1, coord2, visu, 0xFF5050);
			}
			else if (visu->lemin->pipes[ij.x][ij.y] > CONNECTED)
			{
				inner_pipes(visu, &coord1, &coord2, ij);
				draw_square(coord1, coord2, visu, 0x56FF56);
				visu->lemin->pipes[ij.x][ij.y]--;
				visu->lemin->pipes[ij.x][ij.y]--;
			}
		}
	}
}

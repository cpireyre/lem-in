/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_visu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:36:23 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/15 11:13:33 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		display_ant_nb(t_visu *visu)
{
	t_rooms *rooms;
	char	*nb;

	rooms = visu->lemin->rooms;
	while (rooms)
	{
		nb = ft_itoa(rooms->ant_nb);
		mlx_string_put(visu->mlx->m_ptr, visu->mlx->w, rooms->coord.x + 20, \
rooms->coord.y + 20, 0xFF0000, nb);
		free(nb);
		rooms = rooms->next;
	}
}

int			exit_visu(t_visu *visu)
{
	free(visu->ants_pos_v);
	free_rooms(&visu->lemin->rooms);
	free(visu->lemin->pipes);
	free(visu->lemin->start_name);
	free(visu->lemin->end_name);
	free(visu->lemin->usr_in);
	free(visu->lemin);
	exit(0);
}

void		ft_init_mlx(t_visu *visu)
{
	if (!(visu->mlx = malloc(sizeof(t_minilibx))))
		exit(0);
	visu->mlx->w_height = 1200;
	visu->mlx->w_width = 1600;
	visu->mlx->m_ptr = mlx_init();
	visu->mlx->w = mlx_new_window(visu->mlx->m_ptr, visu->mlx->w_width, \
visu->mlx->w_height, "Visualisateur lem-in");
	visu->mlx->img.img_ptr = mlx_new_image(visu->mlx->m_ptr, \
visu->mlx->w_width, visu->mlx->w_height);
	visu->mlx->img.data = (int *)mlx_get_data_addr(visu->mlx->img.img_ptr,
	&visu->mlx->img.bpp, &visu->mlx->img.size_l, &visu->mlx->img.endian);
}

void		empty_rooms(t_visu *visu)
{
	t_rooms *rooms;

	rooms = visu->lemin->rooms;
	while (rooms)
	{
		if (rooms->type == START)
			rooms->ant_nb = visu->lemin->ants;
		else
			rooms->ant_nb = 0;
		rooms = rooms->next;
	}
}

void		ft_room_name(t_visu *visu)
{
	t_rooms *rooms;
	int		color;

	rooms = visu->lemin->rooms;
	while (rooms)
	{
		if (rooms->type == START)
			color = 0;
		else if (rooms->type == END)
			color = 0xFF0000;
		else
			color = W;
		mlx_string_put(visu->mlx->m_ptr, visu->mlx->w, rooms->coord.x, \
rooms->coord.y - 20, color, rooms->name);
		rooms = rooms->next;
	}
}

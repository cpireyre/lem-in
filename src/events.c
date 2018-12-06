/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:30:28 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/05 15:39:04 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_loop_events(t_visu *visu)
{
	if (visu->auto_mode)
		ft_move_ants(visu, REGULAR);
	create_pipes(visu);
	ft_create_image(visu);
	mlx_put_image_to_window(visu->mlx->m_ptr, visu->mlx->w, \
visu->mlx->img.img_ptr, 0, 0);
	if (visu->tuto)
		ft_tutorial(visu);
	if (visu->room_name)
		ft_room_name(visu);
	display_ant_nb(visu);
	return (0);
}

void	ft_reset(t_visu *visu)
{
	int	i;

	i = -1;
	while (++i < visu->lemin->ants)
		visu->ants_pos_v[i] = visu->lemin->start_id;
	visu->lemin->usr_in = visu->reset_usr_in;
	empty_rooms(visu);
}

void	ft_tutorial(t_visu *v)
{
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1050, 10, W, "ESC");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1300, 10, W, "Quit visu");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1050, 40, W, "R");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1300, 40, W, "Reset");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1050, 70, W, "Right and left \
Arrows");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1300, 70, W, "Do/Rewind one \
set of moves");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1050, 100, W, "O");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1300, 100, W, "Display/Toggle \
room names");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1050, 130, W, "A");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1300, 130, W, "Automatic mode");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1050, 160, W, "Space");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1300, 160, W, "Stop auto mode");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1050, 190, W, "Any other key");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1300, 190, W, "Toggle tutorial");
}

int		key_others(int key, t_visu *visu)
{
	t_byte mv;

	mv = visu->mv_done;
	if (key == 124)
		ft_move_ants(visu, REGULAR);
	else if (key == 49)
	{
		if (visu->auto_mode)
			visu->auto_mode = 0;
	}
	else if (key == 123)
	{
		ft_reset(visu);
		if (visu->mv_done)
		{
			while (--mv)
				ft_move_ants(visu, BACKWARDS);
			visu->mv_done--;
		}
	}
	else
		visu->tuto = !(visu->tuto);
	return (0);
}

int		key_events(int key, t_visu *visu)
{
	if (key == 53)
	{
		exit_visu(visu);
	}
	else if (key == 15)
	{
		visu->mv_done = 0;
		ft_reset(visu);
		system("say -v Thomas 'Movements resetted'");
	}
	else if (key == 31)
		visu->room_name = !(visu->room_name);
	else if (key == 0)
	{
		if (!(visu->auto_mode))
			system("say -v Thomas 'AUTOMATIC MODE ACTIVATED'");
		else
			system("say -v Thomas 'AUTOMATIC MODE DESACTIVATED'");
		visu->time = time(NULL);
		visu->auto_mode = !visu->auto_mode;
	}
	else
		key_others(key, visu);
	return (0);
}

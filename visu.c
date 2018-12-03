/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:56:06 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/03 14:03:32 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <time.h>

int	rand_a_b(int a, int b)
{
	return (rand() % (b - a) + a);
}

void	display_ant_nb(t_visu *visu)
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

int		main(void)
{
	t_visu	*visu;
	t_list	*usr_in;
	t_list	*tmp;
	int		i;

	i = -1;
	if (!(visu = ft_memalloc(sizeof(t_visu))))
		return (0);
	if (!(visu->lemin = ft_memalloc(sizeof(t_lemin))))
		return (0);
	usr_in = stdin_to_list();
	visu->reset_usr_in = usr_in;
	tmp = usr_in;
	visu->lemin->usr_in = usr_in;
	parse(&usr_in, &tmp, visu->lemin);
	if (!((visu->ants_pos_v) = ft_memalloc(sizeof(int) * visu->lemin->ants)))
		return (0);
	while (++i < visu->lemin->ants)
		visu->ants_pos_v[i] = visu->lemin->start_id;
	ft_init_mlx(visu);
	ft_background(visu);
	mlx_key_hook(visu->mlx->w, key_events, visu);
	mlx_loop_hook(visu->mlx->m_ptr, ft_loop_events, visu);
	mlx_loop(visu->mlx->m_ptr);
}

int	exit_visu(t_visu *visu)
{
	free(visu->reset_usr_in);
	free(visu->ants_pos_v);
	free_rooms(&visu->lemin->rooms);
	free(visu->lemin->pipes);
	free(visu->lemin->start_name);
	free(visu->lemin->end_name);
	free(visu->lemin);
	exit(0);
}

void		ft_background(t_visu *visu)
{
	int		i;

	i = -1;
	while (++i < visu->mlx->w_width * visu->mlx->w_height)
		visu->mlx->img.data[i] = 0x89663E + rand_a_b(0, 5) * 0x0F0F0F;
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

void	create_pipes(t_visu *visu)
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

void	ft_create_image(t_visu *visu)
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

void	ft_init_mlx(t_visu *visu)
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

void	ft_move_ants(t_visu *visu, t_bool mode)
{
	int		i;
	time_t	time_now;

	time_now = time(NULL);
	if (!(i = 0) && visu->auto_mode && time_now - visu->time < 1)
		return ;
	if (visu->lemin->usr_in->next)
		visu->lemin->usr_in = visu->lemin->usr_in->next;
	else
		return ;
	while (visu->lemin->usr_in->content && ((char *)visu->lemin->usr_in->content)[0] != 'L')
		visu->lemin->usr_in = visu->lemin->usr_in->next;
	while (((char *)visu->lemin->usr_in->content)[i++])
	{
		if ((size_t)i >= ft_strlen(((char *)visu->lemin->usr_in->content)))
			break ;
		add_ant(visu, &(((char *)visu->lemin->usr_in->content)[i]));
		while ((((char *)visu->lemin->usr_in->content)[i] && \
((char *)visu->lemin->usr_in->content)[i++] != 'L'))
			;
		i--;
	}
	visu->time = time(NULL);
	if (mode == REGULAR)
		visu->mv_done++;
}

int		get_room_id(t_rooms *rooms, char *room_name)
{
	int	i;

	i = 0;
	while (rooms)
	{
		if (!ft_strcmp(room_name, rooms->name))
		{
			return (i);
		}
		i++;
		rooms = rooms->next;
	}
	return (0);
}

void	substract_ant(t_visu *visu, int ant_nb)
{
	int		room_id;
	t_rooms *rooms;

	rooms = visu->lemin->rooms;
	room_id = visu->ants_pos_v[ant_nb - 1];
	while (rooms && room_id--)
		rooms = rooms->next;
	rooms->ant_nb--;
}

void	add_ant(t_visu *visu, char *line)
{
	int		i;
	int		j;
	char	*cut_line;
	char	*r_name;
	t_rooms	*rooms;
	int		ant_nb;

	ant_nb = ft_atoi(line);
	rooms = visu->lemin->rooms;
	i = -1;
	j = 1;
	cut_line = ft_strstr(line, "-");
	while (cut_line[j] && ft_isalnum(cut_line[j]))
		j++;
	r_name = ft_strsub(cut_line, 1, j - 1);
	while (rooms)
	{
		if (!ft_strcmp(r_name, rooms->name))
		{
			substract_ant(visu, ant_nb);
			visu->ants_pos_v[ant_nb - 1] = get_room_id(visu->lemin->rooms, r_name);
			rooms->ant_nb += 1;
			free(r_name);
			return ;
		}
		rooms = rooms->next;
	}
}

void	empty_rooms(t_visu *visu)
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

void	ft_reset(t_visu *visu)
{
	int	i;

	i = -1;
	while (++i < visu->lemin->ants)
		visu->ants_pos_v[i] = visu->lemin->start_id;
	visu->lemin->usr_in = visu->reset_usr_in;
	empty_rooms(visu);
}

void	ft_room_name(t_visu *visu)
{
	t_rooms *rooms;
	int		color;

	rooms = visu->lemin->rooms;
	while (rooms)
	{
		if (rooms->type == START)
			color = 0x00BB80;
		else if (rooms->type == END)
			color = 0xD4AF37;
		else
			color = W;
		mlx_string_put(visu->mlx->m_ptr, visu->mlx->w, rooms->coord.x, \
rooms->coord.y - 20, color, rooms->name);
		rooms = rooms->next;
	}
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
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1050, 160, W, "Any other key");
	mlx_string_put(v->mlx->m_ptr, v->mlx->w, 1300, 160, W, "Toggle tutorial");
}

int		key_others(int key, t_visu *visu)
{
	t_byte mv;

	mv = visu->mv_done;
	if (key == 124)
		ft_move_ants(visu, REGULAR);
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

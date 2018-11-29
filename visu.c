/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:56:06 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/29 10:37:22 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main()
{
	t_lemin	*visu;
	t_list	*usr_in;
	t_list	*tmp;
	int		i;

	i = -1;
	if (!(visu = ft_memalloc(sizeof(t_lemin))))
		return (0);
	usr_in = stdin_to_list();
	buf_print_list(usr_in);
	exit(0);
	tmp = usr_in;
	visu->usr_in = usr_in;
	parse(&usr_in, &tmp, visu);
	if (!((visu->ants_positions_v) = ft_memalloc(sizeof(int) * visu->ants)))
		return (0);
	while (++i < visu->ants)
		visu->ants_positions_v[i] = visu->start_id;
	ft_init_mlx(visu);
	ft_background(visu);
	create_pipes(visu);
	ft_create_image(visu);
	mlx_put_image_to_window(visu->mlx->m_ptr, visu->mlx->w ,visu->mlx->img.img_ptr, 0, 0);
	mlx_key_hook(visu->mlx->w, key_events, visu);
	mlx_hook(visu->mlx->w, 17, 0, exit_visu, visu);
	mlx_loop(visu->mlx->m_ptr);
}

int	exit_visu(t_lemin *visu)
{
	exit (0);
	(void) visu;
}

void		ft_background(t_lemin *visu)
{
	int		i;

	i = -1;
	while (++i < visu->mlx->w_width * visu->mlx->w_height)
		visu->mlx->img.data[i] = 0x684821;

}

t_coord		get_coordinates_room(int room_nb, t_lemin *lemin)
{
	t_coord	coord;
	t_rooms *rooms;

	rooms = lemin->rooms;
	while (room_nb--)
		lemin->rooms = lemin->rooms->next;
	coord.x = lemin->rooms->coord->x + 30;
	coord.y = lemin->rooms->coord->y + 30;
	lemin->rooms = rooms;
	return (coord);
}

void	create_pipes(t_lemin *visu)
{
	int	i;
	int	j;
	t_coord coord1;
	t_coord coord2;

	i = -1;
	while (++i < visu->map_size)
	{
		j = -1;
		while (++j < i)
		{
			if (visu->pipes[i][j] == CONNECTED)
			{
				coord1 = get_coordinates_room(i, visu);
				coord2 = get_coordinates_room(j, visu);
				ft_bresenham(coord1, coord2, visu);
			}
		}
	}
}

void	ft_create_image(t_lemin *visu)
{
	int	i;
	int	j;
	t_rooms *rooms;

	rooms = visu->rooms;
	while (visu->rooms)
	{
		i = 0;
		while (i++ < 60)
		{
			j = 0;
			while (j++ < 60)
				visu->mlx->img.data[visu->rooms->coord->x + i + (visu->rooms->coord->y + j) * visu->mlx->w_width] = visu->rooms->ant_nb * 300 * 0x000010;
		}
		visu->rooms = visu->rooms->next;
	}
	visu->rooms = rooms;
}

void	ft_init_mlx(t_lemin *visu)
{
	if (!(visu->mlx = malloc(sizeof(t_minilibx))))
		exit(0);
	visu->mlx->w_height = 1200;
	visu->mlx->w_width = 1600;
	visu->mlx->m_ptr = mlx_init();
	visu->mlx->w = mlx_new_window(visu->mlx->m_ptr, visu->mlx->w_width , visu->mlx->w_height, "Visualisateur lem-in");
	visu->mlx->img.img_ptr = mlx_new_image(visu->mlx->m_ptr, visu->mlx->w_width , visu->mlx->w_height);
	visu->mlx->img.data = (int *)mlx_get_data_addr(visu->mlx->img.img_ptr,
	&visu->mlx->img.bpp, &visu->mlx->img.size_l, &visu->mlx->img.endian);
}

void	ft_move_ants(t_lemin *visu)
{
	int	i;

	i = 0;
	if (visu->usr_in->next)
		visu->usr_in = visu->usr_in->next;
	else
		return ;
	while (visu->usr_in->content && ((char *)visu->usr_in->content)[0] != 'L')
		visu->usr_in = visu->usr_in->next;
	while (((char *)visu->usr_in->content)[i++])
	{
		if ((size_t)i >= ft_strlen(((char *)visu->usr_in->content)))
			break ;
		ft_printf("line sent to add_ant = %s\n", &(((char *)visu->usr_in->content)[i]));
		add_ant(visu ,&(((char *)visu->usr_in->content)[i]));
		while ((((char *)visu->usr_in->content)[i] && ((char *)visu->usr_in->content)[i++] != 'L'))
			;
		i--;
	}
	ft_bzero(visu->mlx->img.data, sizeof(int) * visu->mlx->w_height * visu->mlx->w_width);
	ft_background(visu);
	create_pipes(visu);
	ft_create_image(visu);
	mlx_put_image_to_window(visu->mlx->m_ptr, visu->mlx->w ,visu->mlx->img.img_ptr, 0, 0);
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

void	substract_ant(t_lemin *visu, int ant_nb)
{
	int	room_id;
	t_rooms *rooms;

	ft_printf("ant_nb = %d\n", ant_nb);
	rooms = visu->rooms;
	room_id = visu->ants_positions_v[ant_nb - 1];
	while (rooms && room_id--)
		rooms = rooms->next;
	rooms->ant_nb--;
	ft_printf("room %s has %d ants in\n", rooms->name, rooms->ant_nb);
}

void	add_ant(t_lemin *visu, char *line)
{
	int	i;
	int	j;
	char *room_name;
	t_rooms	*rooms;
	int	ant_nb;

	ant_nb = ft_atoi(line);
	rooms = visu->rooms;
	i = -1;
	j = 1;
	line = ft_strstr(line, "-");
	while (line[j] && ft_isalnum(line[j]))
		j++;
	room_name = ft_strsub(line, 1, j - 1);
	while (rooms)
	{
		if (!ft_strcmp(room_name, rooms->name))
		{
			substract_ant(visu, ant_nb);
			visu->ants_positions_v[ant_nb - 1] = get_room_id(visu->rooms, room_name);
			rooms->ant_nb += 1;
			return ;
		}
		rooms = rooms->next;
	}
}

int		key_events(int key, t_lemin *visu)
{
	if (key == 53)
		exit(0);
	if (key == 124)
		ft_move_ants(visu);
	(void)visu;
	return (0);
}

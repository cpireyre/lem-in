/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 11:38:31 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/08 11:45:31 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_visu_mv(int x, int y, t_visu *visu)
{
	visu->lemin->pipes[x][y] = MV;
	visu->lemin->pipes[y][x] = MV;
}

void	inner_add_ant(t_visu *visu, char *cut_line, int ant_nb, int start_pos)
{
	substract_ant(visu, ant_nb);
	visu->ants_pos_v[ant_nb - 1] = get_room_id(visu->lemin->rooms, cut_line);
	create_visu_mv(visu->ants_pos_v[ant_nb - 1], start_pos, visu);
	free(cut_line);
}

void	inner_pipes(t_visu *visu, t_coord *coord1, t_coord *coord2, \
t_coord ij)
{
	*coord1 = get_coordinates_room(ij.x, visu->lemin);
	*coord2 = get_coordinates_room(ij.y, visu->lemin);
	ft_bresenham(*coord1, *coord2, visu);
}

t_coord	get_coordinates_room(int room_nb, t_lemin *lemin)
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

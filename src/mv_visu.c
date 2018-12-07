/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_visu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:35:14 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/07 12:03:16 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_move_ants(t_visu *visu, t_bool mode)
{
	int		i;
	time_t	time_now;

	time_now = time(NULL);
	i = 0;
	if (test_mv_ants(visu, time_now))
		return ;
	while (visu->lemin->usr_in->next && visu->lemin->usr_in->content && \
((char *)visu->lemin->usr_in->content)[0] != 'L')
		visu->lemin->usr_in = visu->lemin->usr_in->next;
	if (!ft_strstr(visu->lemin->usr_in->content, "-"))
		return ;
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

t_bool	test_mv_ants(t_visu *visu, time_t time_now)
{
	if (visu->auto_mode && time_now - visu->time < 1)
		return (true);
	if (visu->lemin->usr_in->next)
		visu->lemin->usr_in = visu->lemin->usr_in->next;
	return (false);
}

int		get_room_id(t_rooms *rooms, char *room_name)
{
	int	i;

	i = 0;
	while (rooms)
	{
		if (!ft_strcmp(room_name, rooms->name))
			return (i);
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
	if (rooms->ant_nb)
		rooms->ant_nb--;
}

void	create_visu_mv(int x, int y, t_visu *visu)
{
	visu->lemin->pipes[x][y] = MV;
	visu->lemin->pipes[y][x] = MV;
}

void	add_ant(t_visu *visu, char *line)
{
	int		j;
	char	*cut_line;
	char	*rn;
	t_rooms	*rooms;
	int		ant_nb;
	int		start_pos;

	ant_nb = ft_atoi(line);
	rooms = visu->lemin->rooms;
	j = 1;
	cut_line = ft_strstr(line, "-");
	while (cut_line[j] && ft_isalnum(cut_line[j]))
		j++;
	rn = ft_strsub(cut_line, 1, j - 1);
	start_pos = visu->ants_pos_v[ant_nb - 1];
	while (rooms)
	{
		if (!ft_strcmp(rn, rooms->name))
		{
			substract_ant(visu, ant_nb);
			visu->ants_pos_v[ant_nb - 1] = get_room_id(visu->lemin->rooms, rn);
			create_visu_mv(visu->ants_pos_v[ant_nb - 1], start_pos, visu);
			rooms->ant_nb += 1;
			free(rn);
			return ;
		}
		rooms = rooms->next;
	}
	if (!rooms)
		exit(EXIT_FAILURE);
}

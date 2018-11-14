/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:50:59 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/14 18:24:07 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool      send_ants(t_sender *send, t_lemin *lemin)
{
    int     i;
    int     ants_sent;
    int     ants_arrived;
    int     *rooms;

    rooms = ft_memalloc(sizeof(int) * lemin->ants);
    ants_arrived = 0;
    ants_sent = 1;
    while (ants_arrived < lemin->ants)
    {
        i = 1;
        while (i < ants_sent)
        {
            ants_sent += move_ant(i, lemin, rooms[i]);
        //    rooms[i] = mettre nouvelle salle de la fourmi i
            i++;
            ft_printf("\n");
        }
    }
}

t_bool        move_ant(int ant_index, t_lemin *lemin, int room_nb)
{
    t_bool    ret;

    if (room_nb = get_start_id(lemin->paths))
        ret = true;
    else
        ret = false;
//  room_nb = trouver prochaine salle
    ft_printf("L%d- %s ", ant_index, ft_find_room_name(lemin, room_nb));
    return (ret);
}

char        *ft_find_room_name(t_lemin *lemin, int room_nb)
{
    t_rooms *tmp_rooms;

    tmp_rooms = lemin->rooms;
    while (room_nb--)
        tmp_rooms = tmp_rooms->next;
    return (tmp_rooms->name);
}
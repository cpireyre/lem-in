/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:56:06 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/05 14:37:36 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <time.h>

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

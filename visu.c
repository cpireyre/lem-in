/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:56:06 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/27 12:07:21 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main()
{
	t_visu *visu;

	if (!(visu = malloc(sizeof(t_visu))))
		return (0);
	ft_init_mlx(visu);
	mlx_key_hook(visu->mlx->w, key_events, visu);
	mlx_hook(visu->mlx->w, 17, 0, exit_visu, visu);
	mlx_loop(visu->mlx->m_ptr);
}

int		exit_visu(t_visu *visu)
{
	exit(0);
	(void)visu;
}

void	ft_init_mlx(t_visu *visu)
{
	if (!(visu->mlx = malloc(sizeof(t_minilibx))))
		exit(0);
	visu->mlx->m_ptr = mlx_init();
	visu->mlx->w = mlx_new_window(visu->mlx->m_ptr, 1600, 1200, "visu");
	visu->mlx->img.img_ptr = mlx_new_image(visu->mlx->m_ptr, 1600, 1200);
	visu->mlx->img.data = (int *)mlx_get_data_addr(visu->mlx->img.img_ptr,
	&visu->mlx->img.bpp, &visu->mlx->img.size_l, &visu->mlx->img.endian);
}

int		key_events(int key, t_visu *visu)
{
	if (key == 53)
		exit(0);
	(void)visu;
	return (0);
}

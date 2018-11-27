/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:56:06 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/27 16:04:22 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main()
{
	t_lemin	*visu;
	t_list	*usr_in;
	t_list	*tmp;

	if (!(visu = ft_memalloc(sizeof(t_lemin))))
		return (0);
	usr_in = stdin_to_list();
	tmp = usr_in;
	parse(&usr_in, &tmp, visu);
	ft_init_mlx(visu);
	ft_create_image(visu);
	mlx_key_hook(visu->mlx->w, key_events, visu);
	mlx_hook(visu->mlx->w, 17, 0, exit_visu, visu);
	mlx_loop(visu->mlx->m_ptr);
}

int	exit_visu(t_lemin *visu)
{
	exit (0);
	(void) visu;
}

void	ft_create_image(t_lemin *visu)
{
	int	i;
	int	j;

	while (visu->rooms)
	{
		i = 0;
		while (i++ < 70)
		{
			j = 0;
			while (j++ < 70)
				visu->mlx->img.data[visu->rooms->coord->x + i + (visu->rooms->coord->y + j) * visu->mlx->w_width] = 0xFFFFFF;
		}
		visu->rooms = visu->rooms->next;
	}
	mlx_put_image_to_window(visu->mlx->m_ptr, visu->mlx->w ,visu->mlx->img.img_ptr, 0, 0);
}

void	ft_init_mlx(t_lemin *visu)
{
	if (!(visu->mlx = malloc(sizeof(t_minilibx))))
		exit(0);
	visu->mlx->w_height = 1200;
	visu->mlx->w_width = 1600;
	visu->mlx->m_ptr = mlx_init();
	visu->mlx->w = mlx_new_window(visu->mlx->m_ptr, visu->mlx->w_width , visu->mlx->w_height, "visu");
	visu->mlx->img.img_ptr = mlx_new_image(visu->mlx->m_ptr, visu->mlx->w_width , visu->mlx->w_height);
	visu->mlx->img.data = (int *)mlx_get_data_addr(visu->mlx->img.img_ptr,
	&visu->mlx->img.bpp, &visu->mlx->img.size_l, &visu->mlx->img.endian);
}

int		key_events(int key, t_lemin *visu)
{
	if (key == 53)
		exit(0);
	(void)visu;
	return (0);
}

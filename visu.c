/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 10:56:06 by tboissel          #+#    #+#             */
/*   Updated: 2018/11/27 14:04:04 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main()
{
	t_lemin	*visu;
	t_list	*usr_in;
	t_list	*tmp;

	if (!(visu = malloc(sizeof(t_lemin))))
		return (0);
	usr_in = stdin_to_list();
	tmp = usr_in;
	while (usr_in)
	{
		ft_printf("%s\n", usr_in->content);
		usr_in = usr_in->next;
	}
//	parse(&usr_in, &tmp, visu);
	ft_init_mlx(visu);
	mlx_key_hook(visu->mlx->w, key_events, visu);
	mlx_hook(visu->mlx->w, 17, 0, exit_visu, visu);
	mlx_loop(visu->mlx->m_ptr);
}

int	exit_visu(t_lemin *visu)
{
	exit (0);
	(void) visu;
}

void	ft_init_mlx(t_lemin *visu)
{
	if (!(visu->mlx = malloc(sizeof(t_minilibx))))
		exit(0);
	visu->mlx->m_ptr = mlx_init();
	visu->mlx->w = mlx_new_window(visu->mlx->m_ptr, 1600, 1200, "visu");
	visu->mlx->img.img_ptr = mlx_new_image(visu->mlx->m_ptr, 1600, 1200);
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

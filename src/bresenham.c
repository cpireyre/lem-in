/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:16:04 by tboissel          #+#    #+#             */
/*   Updated: 2018/12/03 11:57:28 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_bresenham_low(t_coord p1, t_coord p2, t_visu *visu)
{
	t_coord	d;
	t_coord	point;
	t_coord r;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	r.y = 1;
	if (d.y < 0)
	{
		r.y = -1;
		d.y = -1 * d.y;
	}
	r.x = 2 * d.y - d.x;
	point.y = p1.y;
	point.x = p1.x;
	while (point.x != p2.x)
	{
		ft_draw_point(point, visu);
		if (((point.x++) || (1)) && r.x > 0)
		{
			point.y = point.y + r.y;
			r.x = r.x - 2 * d.x;
		}
		r.x = r.x + 2 * d.y;
	}
}

void	ft_draw_point(t_coord point, t_visu *lemin)
{
	if (point.x >= 0 && point.x < lemin->mlx->w_width && point.y >= 0 &&
	point.y < lemin->mlx->w_height)
	{
		lemin->mlx->img.data[point.x + point.y * lemin->mlx->w_width] = 0;
	}
}

void	ft_bresenham_high(t_coord p1, t_coord p2, t_visu *visu)
{
	t_coord	d;
	t_coord	point;
	t_coord r;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	r.x = 1;
	if (d.x < 0)
	{
		r.x = -1;
		d.x = -1 * d.x;
	}
	r.y = 2 * d.x - d.y;
	point.y = p1.y;
	point.x = p1.x;
	while (point.y != p2.y)
	{
		ft_draw_point(point, visu);
		if (((point.y++) || (1)) && r.y > 0)
		{
			point.x = point.x + r.x;
			r.y = r.y - 2 * d.y;
		}
		r.y = r.y + 2 * d.x;
	}
}

void	ft_bresenham(t_coord p1, t_coord p2, t_visu *visu)
{
	if (abs(p2.y - p1.y) < abs(p2.x - p1.x))
	{
		if (p1.x > p2.x)
			ft_bresenham_low(p2, p1, visu);
		else
			ft_bresenham_low(p1, p2, visu);
	}
	else
	{
		if (p1.y > p2.y)
			ft_bresenham_high(p2, p1, visu);
		else
			ft_bresenham_high(p1, p2, visu);
	}
}

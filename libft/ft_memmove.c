/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 13:20:00 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/11 13:30:10 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, const void *s, size_t len)
{
	t_byte *pd;
	t_byte *ps;

	pd = (t_byte*)d;
	ps = (t_byte*)s;
	if (!len || s == d)
		return (d);
	else if (s > d)
		ft_memcpy(d, s, len);
	else
	{
		while (len--)
			pd[len] = ps[len];
	}
	return (d);
}

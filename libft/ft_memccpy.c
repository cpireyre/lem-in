/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 08:46:35 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/11 13:02:30 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	t_byte *pd;
	t_byte *ps;

	pd = (t_byte*)d;
	ps = (t_byte*)s;
	while (n--)
	{
		*pd = *ps;
		ps++;
		pd++;
		if (*(ps - 1) == (t_byte)c)
			return ((void*)pd);
	}
	return (NULL);
}

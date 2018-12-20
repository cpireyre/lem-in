/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 13:40:44 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/11 13:40:52 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	t_byte *ps;

	ps = (t_byte*)s;
	while (n--)
	{
		if (*ps == (t_byte)c)
			return (ps);
		ps++;
	}
	return (NULL);
}

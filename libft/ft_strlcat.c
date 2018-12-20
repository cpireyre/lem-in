/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 10:07:44 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/09 13:01:11 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*ptr_dest;
	size_t	lensrc;
	size_t	lendst;

	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	ptr_dest = dst;
	ptr_dest += lendst;
	if (lendst >= size)
		return (size + lensrc);
	size -= lendst;
	while (*src && size > 1)
	{
		*ptr_dest = *src;
		size--;
		ptr_dest++;
		src++;
	}
	*ptr_dest = 0;
	return (lensrc + lendst);
}

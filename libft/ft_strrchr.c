/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:59:32 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/13 07:43:02 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t offset;

	offset = ft_strlen(s) + 1;
	while (offset--)
	{
		if (*(s + offset) == c)
			return ((char*)s + offset);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 13:43:33 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/15 12:46:49 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *h, const char *n)
{
	if (!*n)
		return ((char*)h);
	while (!ft_strnequ(h, n, ft_strlen(n)) && *h)
		h++;
	return (*h ? (char*)h : NULL);
}

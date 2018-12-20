/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:03:08 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/13 14:46:29 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	t_byte	*ps1;
	t_byte	*ps2;
	size_t	i;

	ps1 = (t_byte*)s1;
	ps2 = (t_byte*)s2;
	i = 0;
	if (s1 == s2 || !n)
		return (0);
	while (--n && ps1[i] == ps2[i])
		i++;
	return (ps1[i] - ps2[i]);
}

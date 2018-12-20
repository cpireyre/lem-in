/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:42:33 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/16 07:43:33 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	while (ft_isblank(*s) || *s == '\n')
		s++;
	if (!*s)
		return ("\0");
	j = ft_strlen(s);
	while (ft_isblank(s[j - 1]) || s[j - 1] == '\n')
		j--;
	str = ft_strnew(j);
	if (!str)
		return (NULL);
	str = ft_strncpy(str, s, j);
	return (str);
}

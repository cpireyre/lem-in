/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 09:55:16 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/15 11:22:38 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef	unsigned int	t_uint;

char					*ft_strmapi(char const *s, char (*f)(t_uint, char))
{
	char		*new;
	size_t		len;
	t_uint		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	new = ft_strnew(len);
	if (!new)
		return (NULL);
	while (*s)
	{
		*new = f(i, *s);
		new++;
		i++;
		s++;
	}
	return (new - len);
}

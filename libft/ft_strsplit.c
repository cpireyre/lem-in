/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 08:03:24 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/14 13:50:54 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		is_separator(char c, char a)
{
	return (c == a);
}

static char		*ft_strchardup(const char *str, char c)
{
	char	*dup;
	int		i;

	dup = ft_memalloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && !is_separator(str[i], c))
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

static int		ft_count_words(char const *str, char c)
{
	int words;

	words = 0;
	while (*str)
	{
		while (is_separator(c, *str) && *str)
			str++;
		if (*str && !is_separator(c, *str))
			words++;
		while (!is_separator(c, *str) && *str)
			str++;
	}
	return (words);
}

char			**ft_strsplit(const char *str, char c)
{
	char	**split;
	int		words;
	int		i;

	i = 0;
	words = ft_count_words(str, c);
	if (!(split = ft_memalloc(sizeof(char*) * (words + 1))) || !str)
		return (NULL);
	while (i < words)
	{
		while (is_separator(c, *str) && *str)
			str++;
		if (*str && !is_separator(c, *str))
			split[i] = ft_strchardup(str, c);
		while (!is_separator(c, *str) && *str)
			str++;
		i++;
	}
	split[i] = NULL;
	return (split);
}

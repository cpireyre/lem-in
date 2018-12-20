/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcountif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 10:08:29 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/10 08:05:09 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_strcountif(const char *str, t_bool (*check)(char))
{
	int		count;

	count = 0;
	while (*str)
	{
		count += check(*str);
		str++;
	}
	return (count);
}

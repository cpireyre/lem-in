/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 09:31:56 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/26 13:17:51 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		checkbase(char c)
{
	char	*base;
	size_t	i;

	i = 0;
	base = "0123456789ABCDEF";
	while (c != base[i] && base[i])
		i++;
	return (base[i] ? i : 0);
}

int				ft_atoi_base(char *nbr, int base)
{
	int		sum;
	int		sign;

	sum = 0;
	sign = 1;
	while (ft_isspace(*nbr))
		nbr++;
	if (*nbr == '-' || *nbr == '+')
	{
		sign = (*nbr == '-' ? -1 : 1);
		nbr++;
	}
	while (ft_isdigit(*nbr) || ft_isupper(*nbr))
	{
		sum *= base;
		sum += checkbase(*nbr);
		nbr++;
	}
	return (sum * sign);
}

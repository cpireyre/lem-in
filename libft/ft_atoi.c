/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 09:45:06 by cpireyre          #+#    #+#             */
/*   Updated: 2018/07/23 12:12:20 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_atoi(const char *nbr)
{
	intmax_t	sum;
	t_bool		is_negative;

	sum = 0;
	is_negative = false;
	while (ft_isspace(*nbr))
		nbr++;
	if ((is_negative = (*nbr == '-')) || *nbr == '+')
		nbr++;
	while (ft_isdigit(*nbr))
		sum = (sum * 10) + (*(nbr++) - 48);
	return (is_negative ? -sum : sum);
}

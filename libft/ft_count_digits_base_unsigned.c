/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits_base_unsigned.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 09:11:47 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/18 09:44:25 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_digits_base_unsigned(uintmax_t n, int base)
{
	int	count;

	count = 1;
	while ((n = (n / base)))
		count++;
	return (count);
}

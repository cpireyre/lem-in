/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 09:47:58 by cpireyre          #+#    #+#             */
/*   Updated: 2018/09/01 11:25:52 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_assert(t_bool c, const char *y, const char *n)
{
	if (c == true)
		ft_putstr(y);
	else
		ft_putstr(n);
}

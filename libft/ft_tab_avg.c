/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_avg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:15:43 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/14 16:15:44 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tab_avg(int *tab, int size)
{
	int		acc;
	int		idx;

	acc = 0;
	idx = 0;
	while (idx < size)
		acc += tab[idx++];
	return (acc / size);
}

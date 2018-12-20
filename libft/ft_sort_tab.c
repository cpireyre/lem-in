/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 07:56:20 by cpireyre          #+#    #+#             */
/*   Updated: 2018/07/17 08:02:54 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_sort_tab(int *tab, size_t size)
{
	size_t	i;
	size_t	j;

	if (!tab || size < 2)
		return ;
	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j] > tab[j + 1])
				ft_swap_int(&tab[j], &tab[j + 1]);
			j++;
		}
		i++;
	}
}

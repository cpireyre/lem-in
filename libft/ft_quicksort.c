/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 17:56:46 by cpireyre          #+#    #+#             */
/*   Updated: 2018/09/30 17:57:02 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	sort_partitions(int *tab, int left, int right)
{
	int	i;
	int	j;
	int	pivot;

	if (left >= right)
		return ;
	pivot = tab[left];
	i = left;
	j = right;
	pivot = tab[left];
	while (1)
	{
		while (tab[j] > pivot)
			j--;
		while (tab[i] < pivot)
			i++;
		if (i >= j)
			break ;
		ft_swap_int(&tab[j], &tab[i]);
		i++;
		j--;
	}
	sort_partitions(tab, left, i - 1);
	sort_partitions(tab, j + 1, right);
}

void		ft_quicksort(int *tab, int size)
{
	sort_partitions(tab, 0, size - 1);
}

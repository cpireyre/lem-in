/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:11:27 by cpireyre          #+#    #+#             */
/*   Updated: 2018/09/01 11:14:04 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_options(int argc, char **argv)
{
	int		i;
	int		bits;

	bits = 0;
	i = 1;
	while (i < argc)
	{
		if (ft_isoption(argv[i]) == 0)
			return (0);
		else if (ft_isoption(argv[i]) == 1)
		{
			argv[i]++;
			while (*(argv[i]))
			{
				bits = bits | (1 << (*argv[i] - 'a'));
				argv[i]++;
			}
		}
		i++;
	}
	return (bits);
}

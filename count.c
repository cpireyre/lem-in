/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 07:55:45 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/09 07:56:13 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_size_list(t_rooms *rooms)
{
	int	i;

	i = 0;
	while (rooms && ++i)
		rooms = rooms->next;
	return (i);
}

int		count_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i + 1);
}

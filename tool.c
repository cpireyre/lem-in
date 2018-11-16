/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:46:41 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/16 16:46:42 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_start_id(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i][i] != START)
		i++;
	return (i);
}

int		get_end_id(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i][i] != END)
		i++;
	return (i);
}

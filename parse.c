/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:07:17 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/05 16:21:33 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(void)
{
	t_list		*arg;
	char		*line;

	line = NULL;
	while (ft_gnl(0, &line))
		ft_lstappend(&arg, ft_lstnew(line, sizeof(char) * (ft_strlen(line) + 1)));
	while (arg)
	{
		ft_putendl((char*)arg->content);
		arg = arg->next;
	}
	return (0);
}

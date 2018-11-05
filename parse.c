/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:07:17 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/05 16:39:47 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	is_valid_entry(t_list **head)
{
	t_list	*ptr;

	ptr = *head;
	if (ft_isint((char*)ptr->content))
		return (true);
	else
		return (false);
}

void	print_list(t_list **head)
{
	t_list	*ptr;

	ptr = *head;
	while (ptr)
	{
		ft_putendl((char*)ptr->content);
		ptr = ptr->next;
	}
}

int		main(void)
{
	t_list		*arg;
	char		*line;

	line = NULL;
	while (ft_gnl(0, &line))
		ft_lstappend(&arg, ft_lstnew(line, sizeof(char) * (ft_strlen(line) + 1)));
	if (!(arg))
		ft_exit("empty list\n");
	if (!is_valid_entry(&arg))
		ft_exit("some kind of error or other\n");
	ft_putendl("initial check(s) done. printing list now:");
	print_list(&arg);
	return (0);
}

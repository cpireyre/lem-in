/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:04:14 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/14 13:55:27 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **node, t_list *new_node)
{
	if (new_node)
	{
		if (*node)
		{
			ft_lstlast(*node)->next = new_node;
			new_node->next = NULL;
		}
		else
		{
			ft_lstadd(node, new_node);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:46:45 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/16 16:46:46 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_lst_dequeue(t_list **queue, void (*del)(void *, size_t))
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = *queue;
	tmp = NULL;
	while (ptr)
	{
		if (!ptr->next)
			tmp = ptr;
		ptr = ptr->next;
	}
	ft_lstdelone(&ptr, del);
	tmp->next = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:30:21 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/09 17:20:57 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *map;

	map = NULL;
	while (lst)
	{
		ft_lstappend(&map, ft_lstnew(f(lst)->content, f(lst)->content_size));
		lst = lst->next;
	}
	return (map);
}

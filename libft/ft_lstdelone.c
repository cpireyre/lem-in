/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 09:49:00 by cpireyre          #+#    #+#             */
/*   Updated: 2018/04/09 14:22:59 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list **a, void (*del)(void *, size_t))
{
	if (a)
	{
		del((*a)->content, (*a)->content_size);
		ft_memdel((void**)a);
	}
}

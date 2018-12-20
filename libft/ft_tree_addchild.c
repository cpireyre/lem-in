/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_addchild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 13:13:47 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/14 13:14:04 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_addchild(t_tree **tree, t_tree *child)
{
	if (!(*tree)->child)
	{
		child->parent = *tree;
		(*tree)->child = child;
	}
	else
		ft_tree_addsibling(&(*tree)->child, child);
}

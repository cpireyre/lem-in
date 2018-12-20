/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_addsibling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:52:54 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/14 13:12:35 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_addsibling(t_tree **tree, t_tree *sibling)
{
	if (sibling)
	{
		sibling->parent = (*tree)->parent;
		sibling->sibling = (*tree);
		(*tree) = sibling;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 13:13:29 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/25 13:58:28 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_tree_free(t_tree **tree)
{
	if (!tree || !(*tree))
		return ;
	ft_tree_free(&(*tree)->sibling);
	ft_tree_free(&(*tree)->child);
	free((*tree)->content);
	ft_memdel((void**)tree);
}

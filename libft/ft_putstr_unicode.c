/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_unicode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 08:40:13 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/20 08:43:14 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_unicode(wchar_t *ustr)
{
	while (*ustr)
	{
		ft_putchar_unicode(*ustr);
		ustr++;
	}
}

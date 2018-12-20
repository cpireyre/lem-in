/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DdioO.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 10:50:47 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/20 08:46:53 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversions.h"
#include "integer_conversions.h"

void	signed_dec(t_printf *arg)
{
	integer_conversion(arg);
}

void	l_signed_dec(t_printf *arg)
{
	arg->op.length_mod |= MOD_L;
	signed_dec(arg);
}

void	u_octal(t_printf *arg)
{
	integer_conversion(arg);
}

void	l_u_octal(t_printf *arg)
{
	arg->op.length_mod |= MOD_L;
	signed_dec(arg);
}

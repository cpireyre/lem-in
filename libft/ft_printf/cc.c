/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 10:08:06 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/23 10:11:53 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pad_left_text(t_printf *arg)
{
	if (arg->op.fw > 1 && !(arg->op.fl & FLAG_DASH))
		repeat_buf(&arg->buf, PAD, arg->op.fw - 1);
}

void	pad_right_text(t_printf *arg)
{
	if (arg->op.fw > 1 && (arg->op.fl & FLAG_DASH))
		repeat_buf(&arg->buf, PAD, arg->op.fw - 1);
}

void	mb_char(t_printf *arg)
{
	wchar_t		c;

	c = va_arg(*(arg->ap), wchar_t);
	if (c < 2048)
		arg->op.fw -= 1 * !(c < 127);
	else if (c < 65536)
		arg->op.fw -= 2;
	else
		arg->op.fw -= 3;
	pad_left_text(arg);
	putc_buf_unicode(&arg->buf, c);
	pad_right_text(arg);
}

void	unichar(t_printf *arg)
{
	unsigned char	c;

	if (arg->op.length_mod & MOD_L)
		mb_char(arg);
	else
	{
		c = (unsigned char)va_arg(*(arg->ap), int);
		pad_left_text(arg);
		putc_buf(&arg->buf, c);
		pad_right_text(arg);
	}
}

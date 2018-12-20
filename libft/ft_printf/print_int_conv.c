/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:03:22 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/23 10:44:20 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "inttypes.h"
#include "integer_conversions.h"

void			itoa_buf(t_buf *buf, t_integer_data id)
{
	char	number[256];
	char	*basestr;

	ft_bzero(number, sizeof(char) * 256);
	basestr = id.caps ? "0123456789ABCDEF" : "0123456789abcdef";
	if (id.num < 0)
		id.num = ~id.num + 1;
	while (id.digits)
	{
		number[id.digits - 1] = basestr[(id.num % id.base)];
		id.num /= id.base;
		id.digits--;
	}
	putstr_buf(buf, number);
}

void			utoa_buf(t_buf *buf, t_integer_data id)
{
	char	number[256];
	char	*basestr;

	ft_bzero(number, sizeof(char) * 256);
	basestr = id.caps ? "0123456789ABCDEF" : "0123456789abcdef";
	while (id.digits)
	{
		number[id.digits - 1] = basestr[(id.unum % id.base)];
		id.unum /= id.base;
		id.digits--;
	}
	putstr_buf(buf, number);
}

void			pad_left(t_printf *a, t_integer_data id)
{
	if (!(a->op.fl & FLAG_DASH) && !(a->op.fl & FLAG_ZERO) && (id.to_pad > 0))
		repeat_buf(&a->buf, PAD, id.to_pad);
	if (!(id.u) && id.num < 0)
		putc_buf(&a->buf, '-');
	else if (a->op.fl & FLAG_PLUS)
		putc_buf(&a->buf, '+');
	else if (a->op.fl & FLAG_SPACE)
		putc_buf(&a->buf, PAD);
	if (a->conv == 'p' || (id.alt && (id.diff_prec < 1 || id.base == 16)))
	{
		putc_buf(&a->buf, '0');
		if (id.alt == 2 || a->conv == 'p')
			putc_buf(&a->buf, (id.caps) ? 'X' : 'x');
	}
	if ((id.to_pad > 0) && (a->op.fl & FLAG_ZERO))
		repeat_buf(&a->buf, '0', id.to_pad);
	if (id.diff_prec > 0)
		repeat_buf(&a->buf, '0', id.diff_prec);
}

void			pad_right(t_printf *a, t_integer_data id)
{
	if ((id.to_pad > 0) && (a->op.fl & FLAG_DASH))
		repeat_buf(&a->buf, PAD, id.to_pad);
}

void			integer_conversion(t_printf *a)
{
	t_integer_data	id;

	if ((a->op.prec > 0) || (a->op.fl & FLAG_DASH))
		a->op.fl &= (a->op.fl & ~FLAG_ZERO);
	id = get_int_data(a);
	pad_left(a, id);
	if (id.u)
		utoa_buf(&a->buf, id);
	else
		itoa_buf(&a->buf, id);
	pad_right(a, id);
}

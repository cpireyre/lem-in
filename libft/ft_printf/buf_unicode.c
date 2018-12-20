/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_unicode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 09:50:33 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/23 09:52:49 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buf.h"

void	putc_buf_unicode(t_buf *buf, wchar_t uchar)
{
	if (uchar < 128)
		putc_buf(buf, uchar);
	else if (uchar < 2048)
	{
		putc_buf(buf, 0b11000000 | ((uchar >> 6) & 0b00011111));
		putc_buf(buf, 0b10000000 | (uchar & 0b00111111));
	}
	else if (uchar < 65536)
	{
		putc_buf(buf, 0b11100000 | ((uchar >> 12) & 0b00001111));
		putc_buf(buf, 0b10000000 | ((uchar >> 6) & 0b00111111));
		putc_buf(buf, 0b10000000 | (uchar & 0b00111111));
	}
	else
	{
		putc_buf(buf, 0b11110000 | ((uchar >> 18) & 0b00000111));
		putc_buf(buf, 0b10000000 | ((uchar >> 12) & 0b00111111));
		putc_buf(buf, 0b10000000 | ((uchar >> 6) & 0b00111111));
		putc_buf(buf, 0b10000000 | (uchar & 0b00111111));
	}
}

void	putstr_buf_unicode(t_buf *buf, wchar_t *ustr)
{
	while (*ustr)
	{
		putc_buf_unicode(buf, *ustr);
		ustr++;
	}
}

void	putnstr_buf_unicode(t_buf *buf, wchar_t *ustr, int n)
{
	int		i;

	i = 0;
	while (*ustr && i < n)
	{
		if (*ustr < 128)
			i += 1;
		else if (*ustr < 2048)
			i += 2;
		else if (*ustr < 65536)
			i += 3;
		else
			i += 4;
		if (i <= n)
			putc_buf_unicode(buf, *ustr);
		ustr++;
	}
}

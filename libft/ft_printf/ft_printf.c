/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 11:48:29 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/11 15:21:44 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			init_printf(t_printf *data, va_list *ap)
{
	data->ap = ap;
	data->buf.pos = 0;
	data->buf.filedesc = 1;
	data->buf.written = 0;
	data->error = false;
}

int					convert(t_printf *data, const char *format)
{
	size_t	j;
	void	(*conv)(t_printf *);

	j = 1;
	if (format[j] == '%')
		putc_buf(&data->buf, '%');
	else
	{
		while (format[j] && !ft_strchr(CONVERSIONS, format[j]))
			j++;
		if (format[j])
		{
			data->op = get_op(format);
			data->conv = format[j];
			conv = get_conversion(*(format + j));
			conv(data);
		}
	}
	return (j);
}

extern int			ft_printf(const char *format, ...)
{
	t_printf	data;
	va_list		ap;
	size_t		i;

	va_start(ap, format);
	init_printf(&data, &ap);
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%')
			i += convert(&data, format + i);
		else
			putc_buf(&data.buf, format[i]);
		i++;
	}
	flush_buf(&data.buf);
	return (data.error == true ? -1 : data.buf.written);
}

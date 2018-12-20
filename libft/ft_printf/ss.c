/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ss.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 10:10:41 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/23 10:15:02 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strwlen(wchar_t *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		if (*str < 128)
			len += 1;
		else if (*str < 2048)
			len += 2;
		else if (*str < 65536)
			len += 3;
		else
			len += 4;
		str++;
	}
	return (len);
}

int		will_print_ustr(wchar_t *ustr, int prec)
{
	int		i;
	int		umbrella;

	umbrella = 0;
	i = 0;
	while (*ustr && i < prec)
	{
		umbrella = i;
		if (*ustr < 128)
			i += 1;
		else if (*ustr < 2048)
			i += 2;
		else if (*ustr < 65536)
			i += 3;
		else
			i += 4;
		ustr++;
		if (i > prec)
			return (umbrella);
	}
	return (i);
}

void	mb_string(t_printf *arg)
{
	wchar_t	*str;
	int		pad;

	str = va_arg(*(arg->ap), wchar_t*);
	if (!str)
		str = L"(null)";
	pad = arg->op.fw - ((arg->op.fl & FLAG_PREC) ?
			(size_t)ft_min(will_print_ustr(str, arg->op.prec), ft_strwlen(str))
			: ft_strwlen(str));
	if (pad > 0 && !(arg->op.fl & FLAG_DASH))
		repeat_buf(&arg->buf, PAD, pad);
	if (!(arg->op.fl & FLAG_PREC))
		putstr_buf_unicode(&arg->buf, str);
	else
		putnstr_buf_unicode(&arg->buf, str, arg->op.prec);
	if (pad > 0 && (arg->op.fl & FLAG_DASH))
		repeat_buf(&arg->buf, PAD, pad);
}

void	string(t_printf *arg)
{
	char	*str;
	int		pad;

	if (arg->op.length_mod & MOD_L)
	{
		mb_string(arg);
		return ;
	}
	str = va_arg(*(arg->ap), char*);
	if (!str)
		str = "(null)";
	pad = arg->op.fw - (arg->op.fl & FLAG_PREC ?
			(size_t)ft_min(ft_strlen(str), arg->op.prec) : ft_strlen(str));
	if (pad > 0 && !(arg->op.fl & FLAG_DASH))
		repeat_buf(&arg->buf, PAD, pad);
	if (arg->op.fl & FLAG_PREC)
		putnstr_buf(&arg->buf, str, arg->op.prec);
	else
		putstr_buf(&arg->buf, str);
	if (pad > 0 && (arg->op.fl & FLAG_DASH))
		repeat_buf(&arg->buf, PAD, pad);
}

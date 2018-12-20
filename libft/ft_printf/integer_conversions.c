/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_conversions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 09:30:53 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/25 07:56:15 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "integer_conversions.h"

char			get_base(char conv)
{
	if (conv == 'o' || conv == 'O')
		return (8);
	else if (conv == 'x' || conv == 'X' || conv == 'p')
		return (16);
	else
		return (10);
}

t_bool			get_signedness(char conv)
{
	if (conv == 'u'
			|| conv == 'U'
			|| conv == 'o'
			|| conv == 'O'
			|| conv == 'x'
			|| conv == 'X'
			|| conv == 'p')
		return (true);
	else
		return (false);
}

intmax_t		get_cast(t_printf *arg)
{
	intmax_t	i;

	if (arg->op.length_mod & MOD_J)
		i = va_arg(*(arg->ap), intmax_t);
	else if (arg->op.length_mod & MOD_Z)
		i = va_arg(*(arg->ap), size_t);
	else if (arg->op.length_mod & MOD_LL)
		i = va_arg(*(arg->ap), long long int);
	else if (arg->op.length_mod & MOD_L)
		i = va_arg(*(arg->ap), long int);
	else if (arg->op.length_mod & MOD_HH)
		i = (char)va_arg(*(arg->ap), int);
	else if (arg->op.length_mod & MOD_H)
		i = (short int)va_arg(*(arg->ap), int);
	else
		i = va_arg(*(arg->ap), int);
	return (i);
}

uintmax_t		get_unsigned_cast(t_printf *arg)
{
	uintmax_t	i;

	if (arg->op.length_mod & MOD_J)
		i = va_arg(*(arg->ap), uintmax_t);
	else if (arg->op.length_mod & MOD_Z)
		i = va_arg(*(arg->ap), ssize_t);
	else if (arg->op.length_mod & MOD_LL)
		i = va_arg(*(arg->ap), unsigned long long int);
	else if (arg->op.length_mod & MOD_L)
		i = va_arg(*(arg->ap), unsigned long int);
	else if (arg->op.length_mod & MOD_HH)
		i = (unsigned char)va_arg(*(arg->ap), int);
	else if (arg->op.length_mod & MOD_H)
		i = (unsigned short int)va_arg(*(arg->ap), int);
	else
		i = va_arg(*(arg->ap), unsigned int);
	return (i);
}

t_byte			get_alt(t_integer_data id, t_printf *a)
{
	if (a->conv == 'p')
		return (2);
	else if (a->op.fl & FLAG_SHARP)
	{
		if ((id.u && id.unum) || (!id.u && id.num))
		{
			if (id.base == 8)
				return (1);
			else if (id.base == 16)
				return (2);
		}
	}
	return (0);
}

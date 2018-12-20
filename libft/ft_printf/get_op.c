/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 10:14:15 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/08 08:13:22 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_byte	get_fl(const char *spec)
{
	int		i;
	t_byte	fl;
	t_bool	ignore_zero;

	i = -1;
	fl = 0;
	ignore_zero = 0;
	while (spec[++i] && !ft_strchr(CONVERSIONS, spec[i]))
	{
		if ('1' <= spec[i] && spec[i] <= 9)
			ignore_zero = true;
		if (spec[i] == '#')
			fl = fl | (FLAG_SHARP);
		else if (spec[i] == '0' && !ignore_zero)
			fl = fl | (FLAG_ZERO);
		else if (spec[i] == '-')
			fl = fl | (FLAG_DASH);
		else if (spec[i] == PAD)
			fl = fl | (FLAG_SPACE);
		else if (spec[i] == '+')
			fl = fl | (FLAG_PLUS);
		else if (spec[i] == '.')
			fl = fl | (FLAG_PREC);
	}
	return (fl);
}

int		get_prec(const char *spec)
{
	size_t	i;

	i = 0;
	while (spec[i] && !ft_strchr(CONVERSIONS, spec[i]))
	{
		if (spec[i] == '.' && spec[i + 1])
			return (ft_atoi(spec + i + 1));
		i++;
	}
	return (0);
}

int		get_fw(const char *spec)
{
	while (!ft_isdigit(*spec) || *spec == '0')
	{
		if (*spec == '.' || ft_strchr(CONVERSIONS, *spec))
			return (0);
		spec++;
	}
	return (ft_atoi(spec));
}

t_byte	get_length_mod(const char *spec)
{
	size_t	i;
	t_byte	length_mod;

	i = 0;
	length_mod = 0;
	while (spec[i] && !ft_strchr(CONVERSIONS, spec[i]))
	{
		if (spec[i] == 'j')
			length_mod = length_mod | (MOD_J);
		else if (spec[i] == 'z')
			length_mod = length_mod | (MOD_Z);
		else if (spec[i] == 'h')
			length_mod = (length_mod & (MOD_H)) ? \
				(length_mod | (MOD_HH)) : (length_mod | (MOD_H));
		else if (spec[i] == 'l')
			length_mod = (length_mod & (MOD_L)) ? \
				(length_mod | (MOD_LL)) : (length_mod | (MOD_L));
		i++;
	}
	return (length_mod);
}

t_op	get_op(const char *spec)
{
	t_op	op;

	op.fl = get_fl(spec);
	op.fw = get_fw(spec);
	op.prec = get_prec(spec);
	op.length_mod = get_length_mod(spec);
	return (op);
}

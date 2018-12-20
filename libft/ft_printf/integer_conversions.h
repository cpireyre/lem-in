/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_conversions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 09:29:22 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/25 07:55:00 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTEGER_CONVERSIONS_H
# define INTEGER_CONVERSIONS_H

# include "ft_printf.h"

typedef struct		s_integer_data
{
	t_bool		u;
	intmax_t	num;
	uintmax_t	unum;
	int			digits;
	int			to_pad;
	t_bool		display_sign;
	char		base;
	int			diff_prec;
	t_byte		alt;
	t_bool		caps;
}					t_integer_data;

char				get_base(char conv);
t_bool				get_signedness(char conv);
t_integer_data		get_int_data(t_printf *a);
intmax_t			get_cast(t_printf *arg);
uintmax_t			get_unsigned_cast(t_printf *arg);
t_byte				get_alt(t_integer_data id, t_printf *a);

#endif

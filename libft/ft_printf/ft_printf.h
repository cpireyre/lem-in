/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:45:00 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/11 14:54:36 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "buf.h"
# include <stdarg.h>

# define CONVERSIONS	"DdiOoUuXxCcSsp"
# define NBR_CONVERSIONS 14
# define PAD			' '

# define FLAG_DASH	 	(1)
# define FLAG_ZERO		(1 << 1)
# define FLAG_SHARP		(1 << 2)
# define FLAG_SPACE		(1 << 3)
# define FLAG_PLUS		(1 << 4)
# define FLAG_PREC		(1 << 5)

# define MOD_J			(1)
# define MOD_Z			(1 << 1)
# define MOD_H			(1 << 2)
# define MOD_HH			(1 << 3)
# define MOD_L			(1 << 4)
# define MOD_LL			(1 << 5)

typedef struct		s_op
{
	t_byte		fl;
	int			fw;
	int			prec;
	t_byte		length_mod;
}					t_op;

typedef struct		s_printf
{
	va_list		*ap;
	t_op		op;
	t_buf		buf;
	char		conv;
	t_bool		error;
}					t_printf;

typedef void		(*t_func)(t_printf *);

t_op				get_op(const char *spec);
t_func				get_conversion(const char arg);
extern int			ft_printf(const char *format, ...);

# define DEBUG 0

void				print_op(t_printf arg);

#endif

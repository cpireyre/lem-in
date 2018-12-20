/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 11:27:21 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/18 10:56:16 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSIONS_H
# define CONVERSIONS_H

# include "ft_printf.h"
# include "wchar.h"

typedef	struct	s_conv
{
	char	letter;
	void	(*conversion)(t_printf *);
}				t_conv;

/*
** d + i, c. int conversions.
*/

void			signed_dec(t_printf *arg);
void			unichar(t_printf *arg);

/*
 ** o, u, x, X. unsigned int conversions.
*/

void			u_octal(t_printf *arg);
void			u_dec(t_printf *arg);
void			u_hex_low(t_printf *arg);
void			u_hex_upp(t_printf *arg);

/*
** D, O, U. long int conversions.
** I will use these to handle ld, lo, lu, etc. by casting
** arg to long int and calling the following functions. Maybe.
*/

void			l_signed_dec(t_printf *arg);
void			l_u_octal(t_printf *arg);
void			l_u_dec(t_printf *arg);

/*
**  s. const char * conversion.
*/

void			string(t_printf *arg);

/*
** C, S. wint_t and wchar_t * conversions.
*/

void			mb_char(t_printf *arg);
void			mb_string(t_printf *arg);

/*
** p. pointer conversion. similar to %#x.
*/

void			ptr_addr(t_printf *arg);

static const	t_conv g_conversions[NBR_CONVERSIONS] = {
	(t_conv){'d', &signed_dec},
	(t_conv){'i', &signed_dec},
	(t_conv){'c', &unichar},
	(t_conv){'o', &u_octal},
	(t_conv){'u', &u_dec},
	(t_conv){'x', &u_hex_low},
	(t_conv){'X', &u_hex_upp},
	(t_conv){'D', &l_signed_dec},
	(t_conv){'O', &l_u_octal},
	(t_conv){'U', &l_u_dec},
	(t_conv){'s', &string},
	(t_conv){'C', &mb_char},
	(t_conv){'S', &mb_string},
	(t_conv){'p', &ptr_addr}
};

void			integer_conversion(t_printf *a);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 07:54:13 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/25 08:03:05 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "integer_conversions.h"

t_integer_data	get_int_data(t_printf *a)
{
	t_integer_data	id;

	id.u = get_signedness(a->conv);
	id.num = (id.u) ? 0 : get_cast(a);
	id.unum = !(id.u) ? 0 : get_unsigned_cast(a);
	id.base = get_base(a->conv);
	if (id.u)
		id.digits = ft_count_digits_base_unsigned(id.unum, id.base);
	else
		id.digits = ft_count_digits_base(id.num, id.base);
	id.display_sign = (a->op.fl & (FLAG_PLUS | FLAG_SPACE))
		|| (!(id.u) && id.num < 0);
	id.diff_prec = a->op.prec - id.digits;
	id.alt = get_alt(id, a);
	id.caps = a->conv == 'X';
	id.to_pad = a->op.fw
		- (ft_max(id.digits, a->op.prec) + id.display_sign +
				((id.diff_prec <= 0 || id.base == 16) ? id.alt : 0));
	return (id);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:28:41 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/14 13:34:15 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_op(t_printf a)
{
	ft_putendl("---------->");
	ft_putstr("Flags: ");
	ft_print_bits(a.op.fl);
	ft_putstr("\nField width: ");
	ft_putnbr_endl(a.op.fw);
	ft_putstr("Precision: ");
	ft_putnbr_endl(a.op.prec);
	ft_putstr("Length modifier: ");
	ft_print_bits(a.op.length_mod);
	ft_putendl("\n<----------");
}

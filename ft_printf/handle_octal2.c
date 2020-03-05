/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_octal2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/22 13:36:58 by mark           #+#    #+#                */
/*   Updated: 2019/09/29 04:10:43 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_amount_pf(t_container *list, t_number number)
{
	if ((number.number == 0 && list->precision == 0 && list->con != 4) ||
			(list->con != 4 && list->flags & HASH && number.number == 0 &&
				list->precision == 0))
		return (0);
	else if (number.length > list->precision)
		return (number.length);
	else
	{
		if (list->con == 4 && list->flags & HASH && number.number != 0)
			list->precision--;
		return (list->precision);
	}
}

void		check_width_pf(t_container *list, t_number number)
{
	if (number.sign == 1 || list->flags & PLUS || list->flags & SPACE ||
			(list->flags & HASH && number.number != 0))
	{
		if (list->con != 4)
			list->width--;
		list->width--;
	}
}

void		right_padding_pre_zero(t_container *list, t_number number)
{
	check_flags(list, number);
	if (list->width > number.length && list->flags & NUL)
	{
		add_zero(list, list->width - number.length);
		list->width -= number.length;
	}
}

void		pre_itoa_pf_padding(t_container *list,
				t_number number, int letter_case)
{
	if (number.length < list->precision)
		add_zero(list, list->precision - number.length);
	ft_itoa_base_len(list, number, letter_case);
}

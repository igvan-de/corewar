/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_hex.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/22 13:24:33 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/07 17:18:43 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		f_hex(t_container *list)
{
	unsigned long long	i;
	t_number			number;

	i = va_arg(list->ap, unsigned long long);
	number.sign = 0;
	number.base = 16;
	number.number = i;
	cast_itoa_pf_base(list, &number);
	number.length = ft_numlen_ull(number.number, number.base);
	if ((list->flags & NUL && list->flags & MIN) ||
		(list->precision != -1))
		list->flags &= ~(NUL);
	if (list->flags & MIN)
		left_padding_pf_base(list, number, list->con - 5);
	else
		right_padding_pf_base(list, number, list->con - 5);
	return ;
}

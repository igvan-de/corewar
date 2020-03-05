/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_uint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/17 16:55:58 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/11 03:41:38 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./utility/utility.h"

static unsigned long long	cast_itoa_u(t_container *list)
{
	unsigned long long save;

	save = 0;
	if (list->lengthmod == 0)
		save = (unsigned long long)va_arg(list->ap, unsigned int);
	else if (list->lengthmod & LEN_H)
		save = (unsigned long long)(unsigned short int)
			va_arg(list->ap, unsigned int);
	else if (list->lengthmod & LEN_HH)
		save = (unsigned long long)(unsigned char)
			va_arg(list->ap, unsigned int);
	else if (list->lengthmod & LEN_L)
		save = (unsigned long long)va_arg(list->ap, unsigned long);
	else if (list->lengthmod & LEN_LL)
		save = va_arg(list->ap, unsigned long long);
	return (save);
}

void						f_uint(t_container *list)
{
	unsigned long long	i;
	t_number			number;

	if ((list->flags & NUL && list->flags & MIN) ||
			(list->precision != -1 && list->flags & NUL))
		list->flags &= ~(NUL);
	if (list->flags & SPACE)
		list->flags &= ~(SPACE);
	i = cast_itoa_u(list);
	if (list->lengthmod & NUL && list->precision != -1)
		list->lengthmod |= ~(NUL);
	number.sign = 0;
	number.base = 10;
	number.number = i;
	number.length = ft_numlen_ull(number.number, number.base);
	if (list->flags & MIN)
		left_padding_int(list, number);
	else
		right_padding_int(list, number);
	return ;
}

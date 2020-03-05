/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_int.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/21 14:57:56 by mark           #+#    #+#                */
/*   Updated: 2019/10/11 03:38:40 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./utility/utility.h"

static long long	cast_itoa(t_container *list)
{
	long long save;

	save = 0;
	if (list->lengthmod == 0)
		save = (long long)va_arg(list->ap, int);
	else if (list->lengthmod & LEN_H)
		save = (long long)(short int)va_arg(list->ap, int);
	else if (list->lengthmod & LEN_HH)
		save = (long long)(signed char)va_arg(list->ap, int);
	else if (list->lengthmod & LEN_L)
		save = (long long)va_arg(list->ap, long);
	else if (list->lengthmod & LEN_LL)
		save = va_arg(list->ap, long long);
	return (save);
}

static int			get_amount(t_container *list, t_number number)
{
	if (number.number == 0 && list->precision == 0)
		return (0);
	else if (number.length > list->precision)
		return (number.length);
	else
		return (list->precision);
}

void				right_padding_int(t_container *list, t_number number)
{
	int amount;

	amount = get_amount(list, number);
	if (number.sign == 1 || list->flags & PLUS || list->flags & SPACE)
		list->width--;
	if (list->flags & NUL && list->width > amount)
	{
		check_flags(list, number);
		add_zero(list, list->width - amount);
	}
	else if (list->width >= amount && !(list->flags & NUL))
	{
		add_space(list, list->width - amount);
		check_flags(list, number);
	}
	else if (list->width <= amount)
		check_flags(list, number);
	if (number.length < list->precision)
		add_zero(list, list->precision - number.length);
	if (!(number.number == 0 && list->precision == 0))
		ft_itoa_base_len(list, number, 0);
}

void				left_padding_int(t_container *list, t_number number)
{
	int	amount;

	amount = get_amount(list, number);
	check_flags(list, number);
	if (number.length < list->precision)
		add_zero(list, list->precision - number.length);
	if (!(number.number == 0 && list->precision == 0))
		ft_itoa_base_len(list, number, 0);
	if (number.sign == 1 || list->flags & PLUS || list->flags & SPACE)
		list->width--;
	if (list->width > amount && list->flags & NUL)
		add_zero(list, list->width - amount);
	else if (list->width > amount)
		add_space(list, list->width - amount);
}

void				f_int(t_container *list)
{
	long long	i;
	t_number	number;

	i = cast_itoa(list);
	if (list->precision < -1)
		list->precision = -1;
	if ((list->flags & NUL && list->flags & MIN) ||
			(list->precision != -1 && list->flags & NUL))
		list->flags &= ~(NUL);
	number.sign = check_sign(&number, &i);
	number.base = 10;
	number.number = (unsigned long long)i;
	number.length = ft_numlen_ull(number.number, number.base);
	if (list->flags & MIN)
		left_padding_int(list, number);
	else
		right_padding_int(list, number);
	return ;
}

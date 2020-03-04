/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_float.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/22 13:25:47 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/11 03:35:51 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./utility/utility.h"

void				add_sign(t_whole_float *number, t_container *list)
{
	if (list->flags & SPACE && number->nega == 0 && !(list->flags & PLUS))
	{
		addbuff(list, ' ');
		list->width--;
	}
	else if (number->posi == 1 && number->nega == 0)
	{
		addbuff(list, '+');
		list->width--;
	}
	else if (number->posi == 1 && number->nega == 1)
	{
		addbuff(list, '-');
		list->width--;
	}
}

static void			float_decimal(t_container *list, t_float_str *line,
					int length_wholenum, t_whole_float *number)
{
	if (number->whole_num == 0)
		length_wholenum = 1;
	ft_itoa_base_len_float(line, number, length_wholenum, 0);
	if (list->precision != 0)
	{
		line->str[line->length] = '.';
		line->length++;
		while (list->precision > 0)
		{
			number->remaining *= 10;
			ft_itoa_base_len_float(line, number, 1, 1);
			number->remaining = decimal(number->remaining);
			list->precision--;
		}
	}
	number->remaining *= 10;
	rounding(line, (int)number->remaining);
	if (!line->str)
		return ;
}

static void			left_padding_float(t_container *list, char *str,
					t_whole_float *number, int length_wholenum)
{
	int			store;
	t_float_str	line;

	store = list->precision;
	line.length = 0;
	line.str = str;
	add_sign(number, list);
	float_decimal(list, &line, length_wholenum, number);
	add_str(list, line.str);
	if (list->width > (store + 1 + length_wholenum))
		add_space(list, list->width - (store + 1 + length_wholenum));
	free(str);
}

static void			right_padding_float(t_container *list, char *str,
					t_whole_float *number, int length_wholenum)
{
	t_float_str line;

	line.str = str;
	line.length = 0;
	if (list->width > (list->precision + 1 +
		length_wholenum))
		right_float_flags(list, length_wholenum, number);
	else
		add_sign(number, list);
	float_decimal(list, &line, length_wholenum, number);
	add_str(list, line.str);
	free(str);
}

void				f_float(t_container *list)
{
	t_whole_float	number;
	char			*str;
	int				length_wholenum;
	long double		decinum;

	number.sign = 0;
	number.posi = 0;
	if (list->lengthmod & LEN_FL)
		decinum = va_arg(list->ap, long double);
	else
		decinum = (long double)va_arg(list->ap, double);
	if (list->precision == -1)
		list->precision = 6;
	if (nanfin(list, decinum) == 1)
		return ;
	into_def(&number, decinum, &length_wholenum, list);
	str = ft_strnew(length_wholenum + 1 + list->precision + number.sign);
	if (!str)
		return ;
	if (list->flags & MIN)
		left_padding_float(list, str, &number, length_wholenum);
	else
		right_padding_float(list, str, &number, length_wholenum);
}

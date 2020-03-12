/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_float2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 19:29:58 by mlokhors       #+#    #+#                */
/*   Updated: 2019/09/29 06:12:54 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			right_float_flags(t_container *list,
					int length_wholenum, t_whole_float *number)
{
	if (list->flags & NUL)
	{
		add_sign(number, list);
		add_zero(list, (list->width -
			(list->precision + 1 + length_wholenum)));
	}
	else
	{
		add_space(list, (list->width -
			(list->precision + 1 + length_wholenum + number->sign)));
		add_sign(number, list);
	}
}

static int		check_whole_number_double(long double decinum)
{
	int count;

	count = 0;
	if (decinum < (long double)1 && decinum > (long double)0)
		count = 1;
	if (decinum <= 0.0L)
		count = 1;
	while (decinum >= (long double)1)
	{
		decinum /= (long double)10;
		count++;
	}
	return (count);
}

int				search_nega(long double decinum, t_whole_float *number)
{
	if ((long double)1 / decinum == (-1.0 / 0.0))
	{
		number->nega = 1;
		number->sign = 1;
		return (1);
	}
	return (0);
}

void			into_def(t_whole_float *number,
					long double decinum, int *length_wholenum,
					t_container *list)
{
	int check;

	check = search_nega(decinum, number);
	if (check == 1)
		return ;
	number->nega = 0;
	if (decinum < 0.0L || list->flags & PLUS)
	{
		number->posi = 1;
		number->sign = 1;
		if (decinum < 0.0L)
		{
			decinum = -decinum;
			number->nega = 1;
		}
	}
	number->whole_num = (unsigned long long)decinum;
	*length_wholenum = check_whole_number_double(decinum);
	number->remaining = decimal(decinum);
}

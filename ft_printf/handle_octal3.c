/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_octal3.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/29 05:20:30 by mlokhors       #+#    #+#                */
/*   Updated: 2019/09/29 09:07:16 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		o_check_zero_left(t_container *list)
{
	int check;

	check = 0;
	if (list->flags & HASH)
	{
		check = 1;
		addbuff(list, '0');
	}
	if (list->precision > 0)
		add_zero(list, list->precision);
	if (list->width > (list->precision + check) && list->width > 0)
		add_space(list, list->width - list->precision - check);
	return (1);
}

static int		o_check_zero_right(t_container *list)
{
	int		check;

	check = 0;
	if (list->flags & HASH)
		check = 1;
	if (list->width > (list->precision + check) && list->width > 0)
		add_space(list, list->width - list->precision - check);
	if (check == 1)
		addbuff(list, '0');
	if (list->precision > 0)
		add_zero(list, list->precision);
	return (1);
}

int				o_check_zero(t_container *list, t_number number)
{
	if (list->width == -1 && list->precision == -1 && number.number == 0)
	{
		addbuff(list, '0');
		return (1);
	}
	if (list->width == 0 && list->precision == 0 && number.number == 0)
	{
		if (list->flags & HASH)
			addbuff(list, '0');
		return (1);
	}
	if (list->flags & HASH)
		list->precision--;
	if (list->width == -1)
		list->width = 0;
	if (list->precision == -1)
		list->precision = 0;
	if (list->flags & MIN && number.number == 0)
		return (o_check_zero_left(list));
	else
		return (o_check_zero_right(list));
	return (0);
}

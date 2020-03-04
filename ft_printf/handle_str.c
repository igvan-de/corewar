/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_str.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/22 13:21:56 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/11 03:40:38 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./utility/utility.h"

static void		left_padding_str(char *str, t_container *list)
{
	int amount;
	int max;
	int length;

	amount = 0;
	length = ft_strlen(str);
	if (list->precision != -1 && length > list->precision)
		max = list->precision;
	else
		max = length;
	while (*str && amount < max)
	{
		addbuff(list, *str);
		str++;
		amount++;
	}
	if (list->flags & NUL && max < list->width)
		add_zero(list, list->width - max);
	else if (length < list->width)
		add_space(list, list->width - max);
}

static void		right_padding_str(char *str, t_container *list)
{
	int amount;
	int max;
	int length;

	amount = 0;
	length = ft_strlen(str);
	if (list->precision != -1 && length > list->precision)
		max = list->precision;
	else
		max = length;
	if (list->flags & NUL && max < list->width)
		add_zero(list, list->width - max);
	else if (max < list->width)
		add_space(list, list->width - max);
	while (*str && amount < max)
	{
		addbuff(list, *str);
		str++;
		amount++;
	}
}

void			f_string(t_container *list)
{
	char *str;

	str = va_arg(list->ap, char *);
	if (!str)
		str = "(null)";
	if (list->precision < -1)
		list->precision = -1;
	if (list->width != -1 || list->precision != -1)
	{
		if (list->flags & MIN)
			left_padding_str(str, list);
		else
			right_padding_str(str, list);
	}
	else
	{
		while (*str)
		{
			addbuff(list, *str);
			str++;
		}
	}
}

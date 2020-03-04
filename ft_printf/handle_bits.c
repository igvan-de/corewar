/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_bits.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/22 17:07:18 by mark           #+#    #+#                */
/*   Updated: 2019/09/29 14:38:34 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		bits_max(t_container *list, int *space_count)
{
	if (list->bit == 1 || list->bit == 2)
	{
		*space_count = 0;
		return (8);
	}
	else if (list->bit == 3 || list->bit == 4)
	{
		*space_count = 3;
		return (32);
	}
	else if (list->bit == 5 || list->bit == 6)
	{
		*space_count = 1;
		return (16);
	}
	else if (list->bit == 7 || list->bit == 8)
	{
		*space_count = 7;
		return (64);
	}
	else
	{
		*space_count = 15;
		return (128);
	}
}

static void		print_bits(t_container *list, t_bits sort)
{
	int max;
	int i;
	int space_count;

	i = 0;
	max = bits_max(list, &space_count);
	while (i < max)
	{
		if (sort.notsign & (1ULL << (max - 1 - i)))
			addbuff(list, '1');
		else
			addbuff(list, '0');
		if ((i + 1) % 8 == 0 && space_count != 0)
		{
			addbuff(list, ' ');
			space_count--;
		}
		i++;
	}
	return ;
}

static void		long_get_data(t_container *list, t_bits *sort)
{
	if (list->bit == 6 || list->bit == 7)
	{
		if (list->bit == 2)
			sort->sign = va_arg(list->ap, long);
		else
			sort->notsign = va_arg(list->ap, unsigned long);
	}
	else
	{
		if (list->bit == 9)
			sort->sign = va_arg(list->ap, int);
		else
			sort->notsign = va_arg(list->ap, unsigned int);
	}
	return ;
}

static void		get_data(t_container *list, t_bits *sort)
{
	if (list->bit == 1 || list->bit == 2)
	{
		if (list->bit == 1)
			sort->sign = (char)va_arg(list->ap, int);
		else
			sort->notsign = (unsigned char)va_arg(list->ap, unsigned int);
	}
	else if (list->bit == 3 || list->bit == 4)
	{
		if (list->bit == 3)
			sort->sign = va_arg(list->ap, int);
		else
			sort->notsign = va_arg(list->ap, unsigned int);
	}
	else if (list->bit == 5 || list->bit == 6)
	{
		if (list->bit == 5)
			sort->sign = (short)va_arg(list->ap, int);
		else
			sort->notsign = (unsigned short)va_arg(list->ap, unsigned int);
	}
	return ;
}

void			f_bits(t_container *list)
{
	t_bits sort;

	sort.sign = 0;
	if (list->bit == 11)
	{
		print_bits_str(list, sort);
		return ;
	}
	else if (list->bit >= 6 && list->bit <= 10)
		long_get_data(list, &sort);
	else if (list->bit >= 1 && list->bit <= 5)
		get_data(list, &sort);
	if (list->bit <= 0 && list->bit >= 12)
		return ;
	print_bits(list, sort);
}

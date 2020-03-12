/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_memory.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/22 13:21:14 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/07 17:18:38 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		right_padding_pointer(t_container *list,
					t_number number, char *str)
{
	if (list->width > (number.length + 2))
		add_space(list, list->width - number.length - 2);
	add_str(list, str);
	if (list->precision != 0)
		ft_itoa_base_len(list, number, 0);
}

static void		left_padding_pointer(t_container *list,
					t_number number, char *str)
{
	add_str(list, str);
	if (list->precision != 0)
		ft_itoa_base_len(list, number, 0);
	if (list->width > (number.length + 2))
		add_space(list, list->width - number.length - 2);
}

void			f_void_pointer(t_container *list)
{
	void		*pointer;
	t_number	number;
	char		*str;

	str = "0x";
	pointer = va_arg(list->ap, void *);
	number.number = (unsigned long long)pointer;
	number.sign = 0;
	number.base = 16;
	number.length = ft_numlen_ull(number.number, number.base);
	if (list->flags & MIN)
		left_padding_pointer(list, number, str);
	else
		right_padding_pointer(list, number, str);
	return ;
}

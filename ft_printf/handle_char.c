/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_char.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/21 14:57:22 by mark           #+#    #+#                */
/*   Updated: 2019/09/25 18:25:00 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		right_padding_c(char c, t_container *list)
{
	if (list->flags & NUL && list->width != -1)
		add_zero(list, list->width - 1);
	else if (list->width != -1)
		add_space(list, list->width - 1);
	addbuff(list, c);
}

static void		left_padding_c(char c, t_container *list)
{
	addbuff(list, c);
	if (list->flags & NUL && list->width != -1)
		add_zero(list, list->width - 1);
	else if (list->width != -1)
		add_space(list, list->width - 1);
}

void			f_char(t_container *list)
{
	char c;

	c = va_arg(list->ap, int);
	if (list->width == -1)
		addbuff(list, c);
	else
	{
		if (list->flags & MIN)
			left_padding_c(c, list);
		else
			right_padding_c(c, list);
	}
}

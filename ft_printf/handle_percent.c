/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_percent.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/21 20:24:06 by mark           #+#    #+#                */
/*   Updated: 2019/09/25 18:40:40 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		f_percent(t_container *list)
{
	if (list->flags & MIN)
	{
		if (list->width != -1)
		{
			addbuff(list, '%');
			add_space(list, list->width - 1);
		}
		else
			addbuff(list, '%');
	}
	else
	{
		if (list->width != -1)
		{
			if (list->flags & NUL)
				add_zero(list, list->width - 1);
			else
				add_space(list, list->width - 1);
			addbuff(list, '%');
		}
		else
			addbuff(list, '%');
	}
}

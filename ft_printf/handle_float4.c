/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_float4.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/26 09:33:17 by mlokhors       #+#    #+#                */
/*   Updated: 2019/09/29 06:09:36 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		check_space(t_container *list)
{
	if (list->flags & SPACE && !(list->flags & PLUS))
	{
		addbuff(list, ' ');
		list->width--;
	}
}

static void		nanfin_plus(t_container *list, char **nano, int ret)
{
	if (list->flags & MIN)
	{
		check_space(list);
		add_str(list, nano[ret - 1]);
		if (ret == 1 || (ret == 2 && !(list->flags & PLUS)))
			add_space(list, list->width - 3);
		else
			add_space(list, list->width - 4);
	}
	else
	{
		if (ret == 1 || (ret == 2 && !(list->flags & PLUS)))
			add_space(list, list->width - 3);
		else
			add_space(list, list->width - 4);
		check_space(list);
		add_str(list, nano[ret - 1]);
	}
}

static int		check_nanfin(long double number, t_container *list)
{
	if (number != number)
		return (1);
	if (number == 1.0L / 0.0L)
	{
		if (list->flags & PLUS)
			return (4);
		else
			return (2);
	}
	if (number == -1.0 / 0.0L)
		return (3);
	return (0);
}

int				nanfin(t_container *list, long double number)
{
	char	*nano[4];
	int		ret;

	nano[0] = "nan";
	nano[1] = "inf";
	nano[2] = "-inf";
	nano[3] = "+inf";
	ret = check_nanfin(number, list);
	if (ret == 0)
		return (0);
	nanfin_plus(list, nano, ret);
	return (1);
}

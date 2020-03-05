/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   widthprecision.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/21 20:18:02 by mark           #+#    #+#                */
/*   Updated: 2019/10/11 03:45:50 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./utility/utility.h"

static int		num__len(int nb)
{
	int i;

	i = 0;
	if (nb < 0 || nb == 0)
		i = 1;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static int		get_width(char **str, t_container *list)
{
	if (**str == '*')
	{
		list->width = va_arg(list->ap, int);
		if (list->width < 0)
		{
			list->flags |= MIN;
			list->width = -list->width;
		}
		(*str)++;
		return (1);
	}
	if (**str >= '0' && **str <= '9')
	{
		list->width = ft_atoi(*str);
		(*str) += num__len(list->width);
		return (1);
	}
	return (0);
}

static int		get_precision(char **str, t_container *list)
{
	if (**str == '*')
	{
		list->precision = va_arg(list->ap, int);
		(*str)++;
		return (1);
	}
	if (**str >= '0' && **str <= '9')
		list->precision = ft_atoi(*str);
	if (list->precision != -1)
	{
		(*str) += num__len(list->precision);
		return (1);
	}
	if (list->precision == -1)
		list->precision = 0;
	return (0);
}

void			check_widthprecision(char **str, t_container *list)
{
	while (**str == '*' || (**str >= '0' && **str <= '9') || **str == '.')
	{
		if (get_width(str, list) == 1)
			continue;
		if (**str == '.')
		{
			(*str)++;
			if (get_precision(str, list) == 1)
				continue;
		}
		if (ft_strchr("cspdioxXf%u", (int)**str) != NULL)
			return ;
		(*str)++;
	}
}

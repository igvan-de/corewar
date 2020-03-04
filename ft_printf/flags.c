/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flags.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/21 18:46:30 by mark           #+#    #+#                */
/*   Updated: 2019/10/11 03:28:49 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				check_l(char **str, t_container *list)
{
	if (**str == 'l')
	{
		list->lengthmod |= LEN_LL;
		(*str)++;
	}
	else
		list->lengthmod |= LEN_L;
}

void				check_h(char **str, t_container *list)
{
	if (**str == 'h')
	{
		list->lengthmod |= LEN_HH;
		(*str)++;
	}
	else
		list->lengthmod |= LEN_H;
}

void				check_lenthmod(char **str, t_container *list)
{
	if (**str == 'h')
	{
		(*str)++;
		check_h(str, list);
	}
	else if (**str == 'l')
	{
		(*str)++;
		check_l(str, list);
	}
	else if (**str == 'L')
	{
		(*str)++;
		list->lengthmod |= LEN_FL;
	}
}

void				check_flag(char **str, t_container *list)
{
	while (ft_strchr("#0- +", (int)**str) != NULL)
	{
		if (**str == '#')
			list->flags |= HASH;
		if (**str == '0')
			list->flags |= NUL;
		if (**str == '-')
			list->flags |= MIN;
		if (**str == ' ')
			list->flags |= SPACE;
		if (**str == '+')
			list->flags |= PLUS;
		(*str)++;
	}
}

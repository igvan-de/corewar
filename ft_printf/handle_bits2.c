/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_bits2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 11:57:59 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/07 17:19:15 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_bits_str(t_container *list, t_bits sort)
{
	char	*str;
	int		i;

	str = va_arg(list->ap, char *);
	while (*str)
	{
		sort.notsign = *str;
		i = 0;
		while (i < 8)
		{
			if (sort.notsign & (1LL << (7 - i)))
				addbuff(list, '1');
			else
				addbuff(list, '0');
			i++;
		}
		str++;
		if (*str != '\0')
			addbuff(list, ' ');
	}
	return ;
}

static void		pre_check_unsigned(char **str, t_container *list)
{
	(*str)++;
	if (ft_strchr("csidlsz", (int)**str) != NULL)
	{
		if (**str == 'c')
			list->bit = 2;
		else if (**str == 'i' || **str == 'd')
			list->bit = 4;
		else if (**str == 'l')
			list->bit = 8;
		else if (**str == 's')
			list->bit = 6;
		else if (**str == 'z')
			list->bit = 10;
	}
}

void			pre_check_binary(char **str, t_container *list)
{
	(*str)++;
	if (ft_strchr("csidlxzu", (int)**str) != NULL)
	{
		if (**str == 'c')
			list->bit = 1;
		else if (**str == 's')
			list->bit = 11;
		else if (**str == 'i' || **str == 'd')
			list->bit = 3;
		else if (**str == 'l')
			list->bit = 7;
		else if (**str == 's')
			list->bit = 5;
		else if (**str == 'z')
			list->bit = 9;
		else if (**str == 'u')
			pre_check_unsigned(str, list);
	}
}

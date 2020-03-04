/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_print.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/02 14:06:17 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/11 03:43:33 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./utility/utility.h"
#include <stdlib.h>

static void		f_list(t_desc number, t_container *list)
{
	const t_print_var var_list[11] = {
	f_char, f_string, f_void_pointer,
	f_int, f_octal, f_hex, f_hex,
	f_float, f_uint, f_percent, f_bits,
	};

	var_list[number](list);
}

static t_desc	find_descriptor(char c)
{
	size_t			i;
	t_pair			pair;
	const t_pair	lookup_array[12] = {
	{ 'c', E_CHAR }, { 's', E_STRING }, { 'p', E_VOID_POINTER },
	{ 'i', E_INT }, { 'd', E_INT }, { 'o', E_OCTAL },
	{ 'x', E_HEX }, { 'X', E_UHEX }, { 'f', E_FLOAT },
	{ 'u', E_UINT}, { '%', E_PERCENT }, { 'b', E_BITS },
	};

	i = 0;
	while (i < 12)
	{
		pair = lookup_array[i];
		if (c == pair.key)
		{
			return (pair.desc);
		}
		i++;
	}
	return (E_INVALID);
}

/*
** check binary needs an extra check because it accept more flags with the %b
*/

static int		conversion(char **str, t_container *list)
{
	t_desc number;

	number = find_descriptor(**str);
	if (number == -1)
		return (-1);
	list->con = number;
	if (list->con == 10)
		pre_check_binary(str, list);
	f_list(number, list);
	(*str)++;
	return (0);
}

static int		parser(char **str, t_container *list)
{
	empty(list);
	(*str)++;
	if (**str == '\0')
		return (0);
	if (ft_strchr("#0- +", (int)**str) != NULL)
		check_flag(str, list);
	if (ft_strchr("0123456789.*", (int)**str) != NULL)
		check_widthprecision(str, list);
	if (ft_strchr("hlL", (int)**str) != NULL)
		check_lenthmod(str, list);
	if (ft_strchr("cspdioxXf%ub", (int)**str) != NULL)
	{
		if (conversion(str, list) == -1)
			return (-1);
	}
	return (0);
}

int				make_print(t_container *list, char *str)
{
	list->i = 0;
	ft_memset(list->buff, 0, BUFF_SIZE);
	while (*str)
	{
		if (*str == '{')
			str += handle_color(list, ft_strdup(str));
		if (*str == '%')
		{
			if (parser(&str, list) == -1)
				return (-1);
			continue;
		}
		addbuff(list, *str);
		str++;
	}
	list->writer(list);
	return (list->total);
}

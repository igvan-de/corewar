/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_float3.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 19:33:22 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/07 17:17:55 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		ft_base_float(unsigned long long *number, int *stored)
{
	int		store;
	int		temp;
	int		con;
	char	*base_number;

	base_number = "0123456789";
	store = *number / ft_power(10, (*stored - 1));
	temp = store % 10;
	con = base_number[temp];
	*number -= ft_power(10, *stored - 1) * temp;
	return (con);
}

void			ft_itoa_base_len_float(t_float_str *line,
			t_whole_float *wholenum, int length_wholenum, int side)
{
	unsigned long long temp;

	if (side == 1)
		temp = wholenum->remaining;
	else
		temp = wholenum->whole_num;
	while (length_wholenum != 0)
	{
		line->str[line->length] = ft_base_float(&temp, &length_wholenum);
		line->length++;
		length_wholenum--;
	}
	return ;
}

static void		is_nine(t_float_str *line)
{
	while (line->str[line->length] == '9')
	{
		line->str[line->length] = '0';
		if ((line->str[0] == '-' && line->str[0] == '+')
			|| line->length == 0)
		{
			line->str = ft_strjoin("1", line->str);
			break ;
		}
		else
		{
			line->length--;
			if (line->str[line->length] == '.')
				line->length--;
			if (line->str[line->length] >=
					'0' && line->str[line->length] <= '8')
			{
				line->str[line->length]++;
				break ;
			}
			else
				continue;
		}
	}
}

void			rounding(t_float_str *line, int after_precision)
{
	if (after_precision >= 5)
	{
		line->length--;
		if (line->str[line->length] == '9')
		{
			is_nine(line);
			if (!line->str)
				return ;
		}
		else
		{
			if (line->str[line->length] == '.')
				line->length--;
			line->str[line->length]++;
		}
	}
}

long double		decimal(long double remaining)
{
	remaining -= (unsigned long long)remaining;
	return (remaining);
}

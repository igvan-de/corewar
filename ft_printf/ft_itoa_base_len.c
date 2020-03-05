/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base_len.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/17 18:23:42 by mark           #+#    #+#                */
/*   Updated: 2019/10/11 03:29:41 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./utility/utility.h"

char	ft_base(unsigned long long *n, int base, int *stored, int letter_case)
{
	int		store;
	int		temp;
	int		con;
	char	*base_number[2];

	base_number[0] = "0123456789abcdefghijklmnopqrstuvwxyz";
	base_number[1] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	store = *n / ft_power(base, (*stored - 1));
	temp = store % base;
	con = base_number[letter_case][temp];
	*n -= ft_power(base, *stored - 1) * temp;
	return (con);
}

void	ft_itoa_base_len(t_container *list, t_number number, int letter_case)
{
	int store;

	store = number.length;
	if (number.number == 0)
		number.length = 1 + number.sign;
	number.length += number.sign;
	while (number.sign != number.length)
	{
		addbuff(list, ft_base(&(number.number),
			number.base, &store, letter_case));
		number.length--;
		store--;
	}
	return ;
}

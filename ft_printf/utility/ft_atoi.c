/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 11:50:38 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/17 02:46:08 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

int		ft_atoi(const char *str)
{
	int		nega;
	long	result;

	nega = 1;
	result = 0;
	while (ft_isspace((int)*str) == 1)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			nega = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (nega * result);
}

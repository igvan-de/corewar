/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 18:54:24 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 17:43:40 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			res;
	int			neg;

	res = 0;
	i = 0;
	neg = 1;
	while (str[i] && ft_isspace(str[i]) == 1)
		++i;
	if (str[i] == '-')
		neg = -1;
	if (ft_issign(str[i]) == 1)
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * neg);
}

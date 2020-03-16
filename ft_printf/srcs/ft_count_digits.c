/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_digits.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 09:53:56 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 09:54:11 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

size_t	ft_count_digits(char *str)
{
	size_t count;

	count = 0;
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 1)
			count++;
		str++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 11:43:59 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 17:46:32 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	long	int	ft_find_size(long int value, int base)
{
	int i;
	int neg;

	i = 0;
	neg = 0;
	if (value < 0 && base == 10)
		neg = 1;
	value = ft_labs(value);
	while (value > 0)
	{
		value /= base;
		i++;
	}
	return (i + neg);
}

char				*ft_itoa_base(int value, int base)
{
	int			len;
	long int	temp;
	char		*dest;
	char		*tab;

	if (value == 0)
		return (ft_ctostr('0'));
	temp = (long int)value;
	tab = "0123456789abcdef";
	if (base < 2 || base > 16)
		return (NULL);
	len = ft_find_size(temp, base);
	temp = ft_labs(temp);
	dest = ft_strnew(len);
	while (len)
	{
		len--;
		dest[len] = tab[(temp % base)];
		temp /= base;
	}
	if (value < 0 && base == 10)
		dest[0] = '-';
	return (dest);
}

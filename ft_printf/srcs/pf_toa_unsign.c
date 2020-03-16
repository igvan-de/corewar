/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_toa_unsign.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:45:37 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/07 10:11:09 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	adjust_typesize(unsigned long long *value, int typesize)
{
	if (typesize == -2)
		*value = (unsigned char)*value;
	else if (typesize == -1)
		*value = (unsigned short)*value;
	else if (typesize == 0)
		*value = (unsigned int)*value;
	else if (typesize == 1)
		*value = (unsigned long)*value;
	return (typesize);
}

static int	find_size(unsigned long long value, int base)
{
	int i;

	i = 0;
	while (value > 0)
	{
		value /= base;
		i++;
	}
	return (i);
}

char		*pf_toa_unsign(unsigned long long val, int b, int type_size, int a)
{
	int			len;
	char		*dest;
	char		*tab;

	type_size = adjust_typesize(&val, type_size);
	if (val == 0)
		return (ft_ctostr('0'));
	if (a == 2)
		tab = "0123456789ABCDEF";
	else
		tab = "0123456789abcdef";
	len = find_size(val, b);
	dest = ft_strnew(len);
	while (len)
	{
		len--;
		dest[len] = tab[(val % b)];
		val /= b;
	}
	return (dest);
}

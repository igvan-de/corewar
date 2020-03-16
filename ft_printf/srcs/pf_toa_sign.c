/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_toa_sign.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:42:51 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/14 09:56:18 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void			adjust_typesize(long long *value, int typesize)
{
	if (typesize == -2)
		*value = (char)*value;
	else if (typesize == -1)
		*value = (short)*value;
	else if (typesize == 0)
		*value = (int)*value;
	else if (typesize == 1)
		*value = (long)*value;
	else if (typesize == 2)
		*value = (long long)*value;
}

static	int			find_size(long long value, int base)
{
	int i;
	int neg;

	i = 0;
	neg = 0;
	if (value < 0 && base == 10)
		neg = 1;
	value = ft_llabs(value);
	while (value > 0)
	{
		value /= base;
		i++;
	}
	return (i + neg);
}

static char			*get_case(int alphacase)
{
	char *tab;

	if (alphacase == 2)
		tab = ft_strdup("0123456789ABCDEF");
	else
		tab = ft_strdup("0123456789abcdef");
	return (tab);
}

static	int			init_var(int *sign, long long *val, int type_size)
{
	*sign = 0;
	if (*val == 0)
		return (-1);
	adjust_typesize(val, type_size);
	if (*val < 0)
		*sign = 1;
	return (0);
}

char				*pf_toa_sign(long long val, int b, int t, int alph)
{
	int			len;
	char		*dest;
	char		*tab;
	int			sign;

	if (val < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	if (init_var(&sign, &val, t) == -1)
		return (ft_ctostr('0'));
	tab = get_case(alph);
	len = find_size(val, b);
	val = ft_llabs(val);
	dest = ft_strnew(len);
	while (len)
	{
		len--;
		dest[len] = tab[(val % b)];
		val /= b;
	}
	if (sign == 1 && b == 10)
		dest[0] = '-';
	free(tab);
	return (dest);
}

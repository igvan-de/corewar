/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_ltoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:41:44 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 18:42:20 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	long int	is_negative(long int *n)
{
	if (*n < 0)
	{
		*n *= -1;
		return (-1);
	}
	else
		return (0);
}

static size_t		find_length(long int value, long int neg)
{
	size_t len;

	len = 2;
	while (value /= 10)
		len++;
	if (neg == -1)
		return (len + 1);
	else
		return (len);
}

char				*pf_ltoa(long int n)
{
	char			*dest;
	long int		neg;
	long int		ll;
	size_t			len;

	ll = (long)n;
	neg = 0;
	neg = is_negative(&ll);
	len = find_length(ll, neg);
	dest = ft_strnew(len);
	if (!dest)
		return (NULL);
	len--;
	while (len > 0)
	{
		len--;
		dest[len] = 48 + (ll % 10);
		ll = ll / 10;
	}
	if (neg == -1)
		dest[0] = '-';
	return (dest);
}

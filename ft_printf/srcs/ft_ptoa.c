/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 17:52:53 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 17:54:41 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	int	find_size(unsigned long long n, int base)
{
	int count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		count++;
		n /= base;
	}
	return (count);
}

char		*ft_ptoa(void *pointer, int base)
{
	char				*dest;
	unsigned long long	n;
	int					i;

	n = (unsigned long long)pointer;
	i = find_size(n, base);
	dest = ft_strnew(i);
	if (!dest)
		return (0);
	if (pointer == 0)
		dest[0] = '0';
	while (n)
	{
		i--;
		if (n % base > 9)
			dest[i] = n % base - 10 + 'a';
		else
			dest[i] = n % base + '0';
		n /= base;
	}
	return (dest);
}

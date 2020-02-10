/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoalong.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/09 17:49:12 by igvan-de       #+#    #+#                */
/*   Updated: 2019/09/25 16:00:16 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		length(int nb, int base)
{
	int					i;

	i = 0;
	while (nb)
	{
		nb = nb / base;
		i++;
	}
	return (i);
}

char			*itoa_long(long long nb, long long base)
{
	char				*str;
	long long			neg;
	long long			i;

	neg = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		neg = 1;
	}
	str = (char*)ft_memalloc(sizeof(char) * length(nb, base) + 1 + neg);
	i = length(nb, base) + neg - 1;
	str[i + 1] = '\0';
	while (nb)
	{
		if (nb % base >= 10)
			str[i] = nb % base - 10 + 'a';
		else
			str[i] = nb % base + '0';
		nb = nb / base;
		i--;
	}
	if (neg == 1)
		str[i] = '-';
	return (str);
}

char			*itoa_un_long(unsigned long long nb, unsigned long long base)
{
	char				*str;
	unsigned long long	i;

	str = (char*)ft_memalloc(sizeof(char) + length(nb, base) + 1);
	i = length(nb, base) - 1;
	str[i + 1] = '\0';
	while (nb)
	{
		if (nb % base >= 10)
			str[i] = nb % base - 10 + 'a';
		else
			str[i] = nb % base + '0';
		nb = nb / base;
		i--;
	}
	return (str);
}

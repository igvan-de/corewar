/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlen_ull.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/28 15:44:44 by mlokhors       #+#    #+#                */
/*   Updated: 2019/09/25 23:16:34 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_numlen_ull(unsigned long long nb, int base)
{
	int i;

	i = 0;
	if (nb == 0)
	{
		i = 1;
		return (i);
	}
	while (nb != 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}

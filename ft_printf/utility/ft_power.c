/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_power.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/19 13:48:25 by mlokhors       #+#    #+#                */
/*   Updated: 2019/09/25 23:16:23 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

unsigned long long		ft_power(int x, int power)
{
	unsigned long long	number;
	int					i;

	number = 1;
	i = 0;
	while (i < power)
	{
		number *= x;
		i++;
	}
	return (number);
}

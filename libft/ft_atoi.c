/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 18:20:31 by igvan-de       #+#    #+#                */
/*   Updated: 2019/10/28 16:27:37 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned long neg;
	unsigned long sum;
	unsigned long i;

	sum = 0;
	neg = 1;
	i = 0;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\f')
	|| (str[i] == '\t' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + str[i] - '0';
		i++;
	}
	return (sum * neg);
}

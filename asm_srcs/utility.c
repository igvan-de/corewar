/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 09:59:56 by mlokhors       #+#    #+#                */
/*   Updated: 2020/02/29 10:27:57 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int till_power(char letter, int power)
{
	int number;
	int total;
	int	i;

	number = (int)(letter - '`');
	i = 0;
	total = number;
	while (power != 0)
	{
		total *= number;
		power--;
	}
	return (total);
}
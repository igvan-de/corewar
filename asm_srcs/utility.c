/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 09:59:56 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/11 10:01:28 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int till_power(char letter, int power)
{
	int number;
	int total;
<<<<<<< HEAD
	int	i;

	number = (int)(letter - '`');
	i = 0;
=======

	number = (int)(letter - '`');
>>>>>>> master
	total = number;
	while (power != 0)
	{
		total *= number;
		power--;
	}
	return (total);
}

/*
** @brief reverse the bytes by four
**
** @param oct = octal receiving
** @return unsigned	int
*/

unsigned int	rev_endian(unsigned int oct)
{
	return (((oct & 0xff) << 24) + ((oct & 0xff00) << 8) +
		((oct & 0xff0000) >> 8) + ((oct >> 24) & 0xff));
}

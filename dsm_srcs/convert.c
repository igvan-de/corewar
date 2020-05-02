/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 13:11:08 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 13:12:09 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"


int	convert(unsigned char *s, int size)
{
	int				i;
	unsigned int	temp;

	i = 0;
	temp = 0;
	while (i < size)
	{
		temp = temp << 8;
		temp |= s[i];
		i++;
	}
	if (size == 1)
		return ((char)temp);
	else if (size == 2)
		return ((short)temp);
	return ((int)temp);
}

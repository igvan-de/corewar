/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 04:24:04 by mlokhors       #+#    #+#                */
/*   Updated: 2020/02/29 04:24:39 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_strnnchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/25 19:09:37 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/11 03:55:02 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t count)
{
	size_t i;

	i = 1;
	if (count == 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && i < count)
	{
		s1++;
		s2++;
		i++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

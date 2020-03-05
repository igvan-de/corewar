/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/26 13:57:56 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/11 03:54:08 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *str, int ch)
{
	char	a;
	int		i;

	i = 0;
	a = (char)ch;
	while (str[i])
	{
		if (str[i] == a)
			return ((char*)&str[i]);
		i++;
	}
	if (str[i] == a)
		return ((char*)&str[i]);
	return (NULL);
}

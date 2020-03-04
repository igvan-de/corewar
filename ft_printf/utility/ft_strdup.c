/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 13:09:51 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/11 03:54:31 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*a;

	j = 0;
	i = ft_strlen(s1);
	a = (char *)malloc(sizeof(char) * (i + 1));
	if (!a)
		return (NULL);
	while (j < i)
	{
		a[j] = s1[j];
		j++;
	}
	a[j] = '\0';
	return (a);
}

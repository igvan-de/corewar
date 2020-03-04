/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/27 22:11:16 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/11 07:07:16 by mlokhors      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_strink;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new_strink = (char *)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_strink)
		return (NULL);
	while (s1[i])
	{
		new_strink[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new_strink[i + j] = s2[j];
		j++;
	}
	new_strink[i + j] = '\0';
	return (new_strink);
}

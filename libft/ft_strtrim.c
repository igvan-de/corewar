/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/28 12:52:52 by igvan-de       #+#    #+#                */
/*   Updated: 2019/09/25 16:00:16 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_endl(char const *s, int i)
{
	int j;
	int m;

	j = ft_strlen(s);
	if (i == j)
		m = 0;
	else
	{
		while (s[j - 1] == ' ' || s[j - 1] == '\t' ||
		s[j - 1] == '\n' || s[j - 1] == '\v')
			j--;
		m = j - i;
	}
	return (m);
}

char		*ft_strtrim(char const *s)
{
	int			i;
	int			m;
	int			k;
	char		*strim;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v')
		i++;
	m = ft_endl(s, i);
	k = 0;
	strim = (char*)ft_memalloc(sizeof(char) * (m + 1));
	if (!strim)
		return (NULL);
	while (m > 0)
	{
		strim[k] = s[i];
		i++;
		k++;
		m--;
	}
	strim[k] = '\0';
	return (strim);
}

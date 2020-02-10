/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 17:36:24 by igvan-de       #+#    #+#                */
/*   Updated: 2019/09/25 16:00:16 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	const char	*tmp;
	const char	*tmp2;

	if (*needle == '\0')
		return ((char*)haystack);
	i = ft_strlen(needle);
	while (*haystack && len >= i)
	{
		tmp = haystack;
		tmp2 = needle;
		while (*tmp == *tmp2 && *tmp && *tmp2)
		{
			tmp++;
			tmp2++;
			if (*tmp2 == '\0')
				return ((char*)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}

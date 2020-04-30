/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 17:43:55 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/30 17:44:36 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char *tmp;
	const char *tmp2;

	if (*needle == '\0')
		return ((char*)haystack);
	while (*haystack)
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
	}
	return (NULL);
}

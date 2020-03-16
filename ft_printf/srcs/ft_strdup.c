/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 13:36:10 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 17:57:23 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;
	int		len;

	len = 0;
	while (s1[len] != '\0')
		len++;
	dest = ft_strnew(len);
	if (dest)
	{
		i = 0;
		while (s1[i] != '\0')
		{
			dest[i] = s1[i];
			i++;
		}
		return (dest);
	}
	return (0);
}

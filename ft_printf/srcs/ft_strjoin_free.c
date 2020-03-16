/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/06 13:43:00 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/06 13:43:43 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_strjoin_free(char *s1, char *s2, int mode)
{
	char	*dest;
	size_t	destlen;

	if (!s1 || !s2)
		return (NULL);
	dest = NULL;
	destlen = ft_strlen(s1) + ft_strlen(s2);
	if (s1 && s2)
	{
		dest = ft_strnew(destlen);
		if (!dest)
			return (NULL);
		ft_strcpy(dest, s1);
		ft_strcat(dest, s2);
		if (mode == 1 || mode == 3)
			free(s1);
		if (mode == 2 || mode == 3)
			free(s2);
	}
	return (dest);
}

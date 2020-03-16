/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 18:00:37 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 18:01:41 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_strndup(char *src, size_t nb)
{
	size_t	len;
	size_t	dest_len;
	char	*dest;
	size_t	i;

	len = ft_strlen(src);
	if (len == 0)
		return (0);
	dest_len = nb;
	dest = ft_strnew(dest_len);
	if (!dest)
		return (0);
	i = 0;
	while (i < nb && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

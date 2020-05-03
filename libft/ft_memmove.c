/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 17:43:55 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/30 17:44:36 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	unsigned char		*s;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (s < d)
	{
		while (len)
		{
			len--;
			d[len] = s[len];
		}
	}
	else
		ft_memcpy(d, s, len);
	return (d);
}

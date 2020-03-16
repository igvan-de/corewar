/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 13:39:18 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 18:01:54 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_strnew(size_t size)
{
	char *ptr;

	ptr = (char*)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (0);
	ft_memset(ptr, '\0', size + 1);
	return (ptr);
}

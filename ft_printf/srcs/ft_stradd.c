/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stradd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/28 17:55:56 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/05/28 17:56:18 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_stradd(char *target, char *add)
{
	char *dest;

	if (target == 0)
		return (add);
	dest = ft_strjoin_free(target, add, 3);
	return (dest);
}

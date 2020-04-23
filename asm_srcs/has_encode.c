/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   has_encode.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:37:30 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/20 16:42:17 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	has_encode(unsigned char op_code)
{
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   has_encode.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:37:30 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/30 10:24:31 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	@brief	:	check operation for encode byte
**
**	@param	op_code	:	operation code
**
**	has_encode receives an operation code and checks if that
**	operation has an encode byte.
*/

bool	has_encode(unsigned char op_code)
{
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
		return (false);
	return (true);
}

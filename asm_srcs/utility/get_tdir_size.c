/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_champ.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:37:30 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/20 16:42:17 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	@brief	:	get direct value size
**
**	@param	op_code	:	operation code
**
**	get_tdir_size receives an operation code and returns
**	the direct value size of that operation. Can either
**	be four or two bytes.
*/

size_t	get_tdir_size(unsigned char op_code)
{
	if (op_code == 0x09 || op_code == 0x0a || op_code == 0x0b
		|| op_code == 0x0c || op_code == 0x0e || op_code == 0x0f)
		return (2);
	return (4);
}

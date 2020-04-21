/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   has_encode.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	check if an operation has an encode byte
**
**	@param op_code	:	operation code
*/

int	has_encode(unsigned char op_code)
{
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   has_encode.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 08:37:46 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 08:37:47 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	has_encode receives an op_code and checks if that operation
**	has an encoding byte. If it does, the function returns 1,
**	otherwise it returns 0.
*/

int	has_encode(unsigned char op_code)
{
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
		return (0);
	return (1);
}

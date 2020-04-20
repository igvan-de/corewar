/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arg_size.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned char	get_arg_size(int op_code, int one, int two)
{
	if (one == 0 && two == 1)
		return (1);
	else if (one == 1 && two == 0)
		return (get_tdir_size(op_code));
	else if (one == 1 && two == 1)
		return (2);
	return (0);
}

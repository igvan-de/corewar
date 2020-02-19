/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_tdir_size.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 17:50:49 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/19 17:50:50 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	T_DIR can have a different size in bytes depending
**	on the operation that uses it. By calling get_tdir_size with the
**	op_code, this function returns the correct T_DIR size in bytes.
**	return value is either 2 or 4 if correct, 0 if error.
*/

int	get_tdir_size(int op_code)
{
	int tdir_size;
	int tdir_tab[17] = { 0, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4};

	if (op_code <= 0 || op_code > 16)
		return (0);
	tdir_size = tdir_tab[op_code];
	return (tdir_size);
}
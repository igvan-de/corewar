/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_tdir_size.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	get_tdir_size(int op_code)
{
	int			tdir_size;
	static	int	tdir_tab[17] = { 0, 4, 4, 4, 4, 4, 4, 4,
	4, 2, 2, 2, 2, 4, 2, 2, 4};

	if (op_code <= 0 || op_code > 16)
		return (0);
	tdir_size = tdir_tab[op_code];
	return (tdir_size);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arg_value.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 17:17:46 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 20:54:21 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

/*
** @brief Get the arg value object
**
** @param file		= struct containing all data
** @param op_code	= value of op_code
** @param one		= first bit of bitpair
** @param two		= second bit of bitpair
** @return int		= size of bytes
**
** by combaring the first bit and the second bit with 0 or 1,
** we can find if is a T_REG, T_DIR or T_IND
**
** 10			11			01			00
** T_DIR		T_IND		T_REG		empty
**
** by knowing the what kind of operation it is we can return the right value
** also we set the type to the needed type_value (founded in enum t_type struct)
*/

int			get_arg_value(t_file *file, int op_code, int one, int two)
{
	if (one == 0 && two == 1)
	{
		file->type = REG;
		return (1);
	}
	else if (one == 1 && two == 0)
	{
		file->type = DIR;
		return (get_tdir_size(op_code));
	}
	else if (one == 1 && two == 1)
	{
		file->type = IND;
		return (2);
	}
	file->type = NONE;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 13:11:08 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 17:31:13 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

/*
**	@brief:	merge two shorts into an int
**
**	@param one	:	short one
**	@param two	:	short two
*/

static int		to_4bytes(unsigned short one, unsigned short two)
{
	int ret;

	ret = 0;
	ret = ret | ((int)one) << 16;
	ret = ret | (int)two;
	return (ret);
}

/*
**	@brief:	merge two bytes
**
**	@param one	:	byte one
**	@param two	:	byte two
*/

static short	to_2bytes(unsigned char one, unsigned char two)
{
	short ret;

	ret = 0;
	ret = ret | ((short)one) << 8;
	ret = ret | (short)two;
	return (ret);
}

/*
** @brief returns value to print
**
** @param index		= current byte index
** @param exec		= executable
** @param arg_size	= size of argument
** @return int 		= value of argument
**
** convert receives executable in binary form and transforms it into an integer
*/

int				convert(int index, char *exec, int arg_size)
{
	if (arg_size == 1)
		return (exec[index]);
	else if (arg_size == 2)
		return (to_2bytes(exec[index], exec[index + 1]));
	else if (arg_size == 4)
	{
		return (
			to_4bytes(
				to_2bytes(
					exec[index], exec[index + 1]),
				to_2bytes(
					exec[index + 2], exec[index + 3])));
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rev_endian.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 14:08:43 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/20 14:08:43 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	reverse the endianness of a 4-byte number
*/

unsigned	int	rev_endian(unsigned int oct)
{
	return (((oct & 0xff) << 24) + ((oct & 0xff00) << 8) +
		((oct & 0xff0000) >> 8) + ((oct >> 24) & 0xff));
}

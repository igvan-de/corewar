/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rev_endian.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	reverse the endianness of a four byte number
**
**	@param oct	:	target number
*/

unsigned	int	rev_endian(unsigned int oct)
{
	return (((oct & 0xff) << 24) + ((oct & 0xff00) << 8) +
		((oct & 0xff0000) >> 8) + ((oct >> 24) & 0xff));
}

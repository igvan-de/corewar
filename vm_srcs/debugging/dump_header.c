/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_header.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	print the contents of a t_header
**
**	@param header	:	target header to print
**
**	dump_header is a debug function used to print
**	and inspect a header struct.
*/

void	dump_header(t_header header)
{
	ft_putstr("\n\n<------ PLAYER HEADER DUMP ------->\n\n\n");
	ft_printf("\n	magic value: %#0x\n", rev_endian(header.magic));
	if (rev_endian(header.magic) == COREWAR_EXEC_MAGIC)
		ft_putendl("		---> magic is valid!\n");
	else
		ft_putendl("		---> error: magic is invalid!");
	ft_printf("	name:				%s\n", header.prog_name);
	ft_printf("	prog size:			%u\n", rev_endian(header.prog_size));
	ft_printf("	comment:			%s\n", header.comment);
}

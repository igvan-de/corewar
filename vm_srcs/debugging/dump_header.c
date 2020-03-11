/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_header.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 14:57:12 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 17:19:41 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	dump_header(header_t header)
{
	ft_putstr("\n\n<------ PLAYER HEADER DUMP ------->\n\n\n");
	printf("\n	magic value: %#0x\n", rev_endian(header.magic));
	if (rev_endian(header.magic) == COREWAR_EXEC_MAGIC)
		ft_putendl("		---> magic is valid!\n");
	else
		ft_putendl("		---> error: magic is invalid!");
	printf("	name:				%s\n", header.prog_name);
	printf("	prog size:			%u\n", rev_endian(header.prog_size));
	printf("	comment:			%s\n", header.comment);
}

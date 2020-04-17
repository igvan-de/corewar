/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_champ_code.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 14:51:53 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 17:19:04 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	print a players' header and execution code to stdout
**
**	@param p			:	target player
**	@param env 			:	global environment struct
**
**	dump_champ is a debugging function with which the contents of a player
**	struct can be printed to stdout.
*/

void	dump_champ_code(t_player *p, t_env *env)
{
	dump_header(*(p->header));
	dump_exec_code(p->exec_code, rev_endian(p->header->prog_size), env);
}

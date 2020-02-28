/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_champ_code.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 14:51:53 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/20 14:51:53 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	open .cor file and print header + execution code
*/

void	dump_champ_code(t_player *p, t_env *env)
{
	dump_header(*(p->header));
	dump_exec_code(p->exec_code, rev_endian(p->header->prog_size), env);
}

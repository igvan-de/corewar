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

void	dump_champ_code(t_player *player, t_env *env)
{
	dump_header(*(player->header));
	dump_exec_code(player->exec_code, rev_endian(player->header->prog_size), env);
}

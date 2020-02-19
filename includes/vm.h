/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vm.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 08:47:01 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/18 09:02:29 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

#include "libft.h"
#include "op.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

/*
**	global environment struct containg main reference data and ptrs (initialized once)
*/

typedef struct	s_env
{
	t_op op_tab[17];
}				t_env;

/* 
**	initialization
*/

void	load_optab(t_env *env);

/*
**	utility
*/

int		get_tdir_size(int opcode);
int		get_bit(unsigned char octet, int index);
void	print_bits(unsigned char octet);

/*
**	printing
*/

void	print_op_name(int op_code, t_env *env);
void	dump_prog_code(char *prog_code, unsigned int prog_size, t_env *env);

#endif

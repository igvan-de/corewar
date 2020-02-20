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
**	struct for each player
*/

typedef struct	s_player
{
	int			player_nb;
	header_t 	*header;
	char		*exec_code;
}				t_player;

/*
**	global environment struct containing main reference data and ptrs (initialized once)
*/

typedef struct	s_env
{
	int			players;
	t_op		op_tab[17];
	t_player	player;								// current dev version only support one player
	char		map[MEM_SIZE];
}				t_env;

/* 
**	initialization
*/

void	load_optab(t_env *env);

/*
**	bitwise manipulation
*/

int				get_bit(unsigned char octet, int index);
void			print_bits(unsigned char octet);
int				to_4bytes(unsigned short one, unsigned short two);
short			to_2bytes(unsigned char one, unsigned char two);
unsigned	int	rev_endian(unsigned int oct);

/*
**	utility
*/

void			exit_usage();
int				get_tdir_size(int opcode);

/*
**	printing
*/

void	print_op_name(int op_code, t_env *env);
void	dump_header(header_t header);												// print header
void	dump_exec_code(char *exec_code, unsigned int prog_size, t_env *env);		// print exec code
void	dump_champ_code(char *champ, t_env *env);									// print header and exec code

#endif

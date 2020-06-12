/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vm.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 17:26:16 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 17:26:17 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <ncurses.h>
# include <time.h>

# define ALL 7

typedef	unsigned char	t_byt;

/*
**	struct to store additional memory cell information
*/

typedef struct			s_datamap
{
	char				cursor;
	char				player;
}						t_datamap;

/*
**	struct for each player
*/

typedef struct			s_player
{
	t_header			*header;
	char				*exec_code;
	int					nbr;
}						t_player;

/*
**	bidirectional cursor struct to simulate processes
*/

typedef	struct			s_cursor
{
	struct s_cursor		*next;
	struct s_cursor		*prev;
	int					*registries;
	int					live_counter;
	unsigned	char	op_code;
	unsigned			id;
	unsigned			carry;
	unsigned			last_live;
	unsigned			wait_cycles;
	int					position;
	unsigned			jump;
}						t_cursor;

/*
**	global environment struct containing reference data
*/

typedef struct			s_env
{
	int					cycles;
	int					cycles_to_die;
	unsigned	char	flag_byte;
	int					player_last_alive;
	int					player_nbr;
	int					curr_nbr;
	int					custom_nbrs;
	unsigned			total_players;
	unsigned			total_cursors;
	unsigned			total_cycles;
	unsigned			cycle_last_check;
	unsigned			live_counter;
	unsigned			checks_counter;
	unsigned			dump_cycle;
	unsigned			verbosity;
	char				*map;
	t_datamap			*datamap;
	t_op				op_tab[17];
	t_list				*players;
	t_cursor			*cursor_stack;
}						t_env;

/*
**	initialization
*/

void					add_player(char *player, t_env *env);
void					init_cursors(t_env *env);
void					init_env(t_env **env);
void					load_optab(t_env *env);
void					load_players(t_env *env);
void					parse_args(int arg_nb, char **argv, t_env *env);
void					nbr_players(t_env *env);

/*
**	program execution
*/

void					announce_winner(t_env *env);
void					check_corewar(t_env *env);
void					exec_corewar(t_env *env);
void					exec_op(t_cursor *cursor, t_env *env);
void					free_env(t_env **env);
void					intro_players(t_env *env);
void					move_cursor(t_cursor *cursor, t_env *env);
void					move_cursor_encode(t_cursor *cursor, t_env *env,
						t_byt enc, t_byt op_code);
void					set_carry(t_cursor *cursor, int mode);
int						valid_encode(t_byt op_code, t_byt encode, t_env *env);
void					process_flag(char **argv, int *i, int nb, t_env *env);

/*
**	operation functions
*/

void					invalid_op(t_cursor *cursor, t_env *env, int type);
void					op_add(t_cursor *cursor, t_env *env);
void					op_and(t_cursor *cursor, t_env *env);
void					op_fork(t_cursor *cursor, t_env *env);
void					op_ld(t_cursor *cursor, t_env *env);
void					op_ldi(t_cursor *cursor, t_env *env);
void					op_lfork(t_cursor *cursor, t_env *env);
void					op_live(t_cursor	*cursor, t_env *env);
void					op_lld(t_cursor *cursor, t_env *env);
void					op_lldi(t_cursor *cursor, t_env *env);
void					op_or(t_cursor *cursor, t_env *env);
void					op_st(t_cursor *cursor, t_env *env);
void					op_sti(t_cursor *cursor, t_env *env);
void					op_sub(t_cursor *cursor, t_env *env);
void					op_xor(t_cursor *cursor, t_env *env);
void					op_zjmp(t_cursor *cursor, t_env *env);
void					op_aff(t_cursor *cursor, t_env *env);

/*
**	utility
*/

int						count_registers(t_byt encode);
void					cpy_reg_vals(t_cursor *dst, t_cursor *src);
t_cursor				*dup_cursor(t_cursor *src, t_env *env);
int						get_arg(t_cursor *c, t_env *env, t_byt enc, int num);
unsigned char			get_arg_size(int op_code, int one, int two);
int						get_bit(t_byt octet, int index);
int						get_reg_num(t_cursor *c, t_env *e, t_byt enc, int num);
int						get_tdir(t_env *env, int position);
int						get_tdir_size(int opcode);
short					get_tind(t_env *env, int position);
unsigned char			get_total_arg_size(t_byt op_code, t_byt encode);
int						get_type(t_byt encode, int arg_num);
int						has_encode(t_byt op_code);
int						*init_registries(void);
unsigned int			modi(int index);
void					push_cursor(t_cursor *c, t_cursor **stack);
unsigned int			rev_endian(unsigned int oct);
short					to_2bytes(unsigned char one, unsigned char two);
int						to_4bytes(unsigned short one, unsigned short two);
int						valid_regs(t_cursor *cursor, t_env *env, t_byt encode);
void					write_bytes(int val, t_env *e, t_cursor *c, int pos);

/*
**	printing
*/

void					dump_champ_code(t_player *player, t_env *env);
void					dump_cursor_stack(t_cursor *cursor_stack);
void					dump_env_state(t_env *env);
void					dump_exec_code(char *exc, unsigned int size, t_env *e);
void					dump_header(t_header header);
void					dump_mem(t_env *env);
void					dump_mem_alt(t_env *env);
void					dump_op(t_cursor *cursor, t_env *env);
void					dump_op_enc(t_cursor *c, t_env *e, t_byt enc, t_byt op);
void					dump_op_invalid(t_cursor *c, t_env *env, t_byt bytes);
void					dump_players(t_list *players, t_env *env);
void					dump_pos(t_env *env);
void					print_bits(unsigned char octet);
void					print_op_name(int op_code, t_env *env);

/*
**	error handlers
*/

void					error_exec(int err_code);
void					error_init(int err_code);
void					error_input(int err_code);
void					error_mem();
void					exit_usage();

/*
**	visualizer
*/

void					init_ncurses(t_env *env);
void					print_map(t_env *env);

#endif

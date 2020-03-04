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

#include <ncurses.h>
#include <time.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define BYTE unsigned char

/*
**	struct for each player
*/

typedef struct			s_player
{
	header_t			*header;				//	ptr to header bytes of player
	char				*color;					//	color as str
	char				*exec_code;				//	ptr to execution code of player
	int					nbr;					//	player number
}						t_player;

/*
**	bidirectional cursor struct to simulate processes
*/

typedef	struct			s_cursor
{
	struct	s_cursor	*next;					//	ptr to next cursor in the stack
	struct	s_cursor	*prev;					//	ptr to previous cursor in the stack
	unsigned			id;						//	unique cursor id
	unsigned			carry;					//	flag which can be changed by certain operations (true (1)or false (0))
	unsigned	char	op_code;				//	operation_code stored at the current position of the cursor
	unsigned			last_live;				//	number of cycle in which current cursor performed operation live last time
	int					live_counter;			//	how many live counters did this cursor execute during the last CTD iteration.
	unsigned			wait_cycles;			//	amount of cycles to wait before operation execution
	unsigned			position;				//	index of current position in memory
	unsigned			jump;					//	amount of bytes cursor must jump to get to the next operation
	int					*registries;			//	registries of current cursor // REG_NUMBER of registries with REG_SIZE bytes per registry
}						t_cursor;

/*
**	global environment struct containing main reference data and ptrs (initialized once)
*/

typedef struct			s_env
{
	unsigned	char	flag_byte;				//	keeps track of corewar program flags (-visual / -n_dump_cycles)	
	unsigned			total_players;			//	total amount of players loaded. Between 0 and 4.
	unsigned			total_cursors;			//	total amount of cursors in the cursor stack
	unsigned	char	player_last_alive;		//	the id of the player who last executed a live operation
	int					cycles;					//	cycle counter of each CYCLE_TO_DIE
	unsigned			total_cycles;			//	total cycle counter
	unsigned			cycle_last_check;		//	cycle number of last check performed
	unsigned			live_counter;			//	keeps track of how many live operations where execution during last CYCLE_TO_DIE cycles
	int					cycles_to_die;			//	length of current check period. Decreases by CYCLE_DELTA, every CYCLE_TO_DIE cycles.
	unsigned			checks_counter;			//	amount of checks performed
	unsigned			dump_cycle;				// if -dump flag enabled --> stores the cycle_nbr
	unsigned			verbosity;				//	if -v flag enabled --> stores the verbosity level
	t_op				op_tab[17];				//	operation reference table
	t_list				*players;				//	list of players.
	char				*map;					//	ptr to main memory map.
	char				*player_pos;			//	ptr to secondary memory map --> keeps track of player positions.
	t_cursor			*cursor_stack;			//	ptr to cursor stack.
}						t_env;

/* 
**	initialization
*/

void					init_env(t_env **env);
void					load_optab(t_env *env);
void					add_player(char *player, t_env *env);
void					set_color(t_player *player);
void					load_players(t_env *env);
void					init_cursors(t_env *env);

/*
**	program execution
*/

void					exec_corewar(t_env *env);
void					check_corewar(t_env *env);
void					move_cursor(t_cursor *cursor, t_env *env);
void					move_cursor_encode(t_cursor *cursor, t_env *env, unsigned char encode, unsigned char op_code);
void					set_carry(t_cursor *cursor, int mode);
int						valid_encode(BYTE op_code, BYTE encode, t_env *env);
void					free_env(t_env **env);
void					intro_players(t_env *env);
void					announce_winner(t_env *env);

/*
**	operation functions
*/

void					op_sti(t_cursor *cursor, t_env *env);
void					op_live(t_cursor	*cursor, t_env *env);
void					op_ld(t_cursor *cursor, t_env *env);
void					op_zjmp(t_cursor	*cursor, t_env *env);
void					invalid_op(t_cursor *cursor, t_env *env, int type);

/*
**	utility
*/

int						get_bit(unsigned char octet, int index);
int						to_4bytes(unsigned short one, unsigned short two);
short					to_2bytes(unsigned char one, unsigned char two);
unsigned	int			rev_endian(unsigned int oct);
int						get_tdir_size(int opcode);
unsigned char			get_arg_size(int op_code, int one, int two);
int						has_encode(unsigned char op_code);
int						count_registers(unsigned char encode);
unsigned char			get_total_arg_size(unsigned char op_code, unsigned char encode);
unsigned int			modi(int index);
void					write_bytes(int target_val, t_env *env, t_cursor *c, int rel_pos);

/*
**	printing
*/

void					print_bits(unsigned char octet);
void					print_op_name(int op_code, t_env *env);
void					dump_header(header_t header);
void					dump_exec_code(char *exec_code, unsigned int prog_size, t_env *env);
void					dump_champ_code(t_player *player, t_env *env);
void					dump_mem(t_env *env);
void					dump_players(t_list *players, t_env *env);
void					dump_cursor_stack(t_cursor *cursor_stack);
void					dump_env_state(t_env *env);
void					dump_op(t_cursor *cursor, t_env *env);
void					dump_op_encode(t_cursor *cursor, t_env *env, unsigned char encode, unsigned char op_code);
void					dump_op_invalid(t_cursor *cursor, t_env *env, unsigned char bytes);

/* 
**	error handlers
*/

void					exit_usage();
void					error_input(int err_code);
void					error_mem();
void					error_init(int err_code);
void					error_exec(int err_code);

/*
**	visualizer
*/

void					init_ncurses(t_env *env);
void					print_map(t_env *env);

#endif

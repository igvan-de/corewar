/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vm.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 08:47:01 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 17:22:50 by ygroenev      ########   odam.nl         */
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

#define BYTE unsigned char

typedef struct	s_datamap
{
	char	cursor;
	char	player;
}				t_datamap;

/*
**	struct for each player
*/

typedef struct			s_player
{
	header_t			*header;				//	ptr to header bytes of player
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
	int					*registries;			//	registries of current cursor // REG_NUMBER of registries with REG_SIZE bytes per registry
	int					live_counter;			//	how many live counters did this cursor execute during the last CTD iteration.
	unsigned	char	op_code;				//	operation_code stored at the current position of the cursor
	unsigned			id;						//	unique cursor id
	unsigned			carry;					//	flag which can be changed by certain operations (true (1)or false (0))
	unsigned			last_live;				//	number of cycle in which current cursor performed operation live last time
	unsigned			wait_cycles;			//	amount of cycles to wait before operation execution
	unsigned			position;				//	index of current position in memory
	unsigned			jump;					//	amount of bytes cursor must jump to get to the next operation
}						t_cursor;

/*
**	global environment struct containing main reference data and ptrs (initialized once)
*/

typedef struct			s_env
{
	int					cycles;					//	cycle counter of each CYCLE_TO_DIE
	int					cycles_to_die;			//	length of current check period. Decreases by CYCLE_DELTA, every CYCLE_TO_DIE cycles.
	unsigned	char	flag_byte;				//	keeps track of corewar program flags (-visual / -n_dump_cycles)
	int					player_last_alive;		//	the id of the player who last executed a live operation
	id_t				player_nbr;				//	used during input reading to keep track of player nbrs
	unsigned			total_players;			//	total amount of players loaded. Between 0 and 4.
	unsigned			total_cursors;			//	total amount of cursors in the cursor stack
	unsigned			total_cycles;			//	total cycle counter
	unsigned			cycle_last_check;		//	cycle number of last check performed
	unsigned			live_counter;			//	keeps track of how many live operations where execution during last CYCLE_TO_DIE cycles
	unsigned			checks_counter;			//	amount of checks performed
	unsigned			dump_cycle;				// if -dump flag enabled --> stores the cycle_nbr
	unsigned			verbosity;				//	if -v flag enabled --> stores the verbosity level
	char				*map;					//	ptr to main memory map.
	t_datamap			*datamap;				//	ptr to secondary memory map --> keeps track of player positions.
	t_op				op_tab[17];				//	operation reference table
	t_list				*players;				//	list of players.
	t_cursor			*cursor_stack;			//	ptr to cursor stack.
}						t_env;

/*
**	initialization
*/

/*
**	@brief: take a program parameter and store it as a corewar player
**
**	@param arg		: corewar program parameter
**	@param env		: global environment struct
**
**	add_player takes a ptr to a program parameter (arg) and parses
**	this parameter as a player. A new t_player struct is created,
**	with the header stored in player->header and the execution_code
**	in player->exec_code. The player is also given a unique number.
**	If the given argument is not a valid player, the function returns error.
**	The new player is stored within the players list in the main env struct at
**	env->players.
*/
void					add_player(char *player, t_env *env);

/*
**	@brief:	initialize the cursor stack
**
**	@param env	:	global environment struct
**
**	init_cursors sets up the initial cursor_stack variable of env, at
**	the beginning of the program.
**	For each active player, a new cursor is created with a position
**	pointing to the first byte of the execution code.
*/
void					init_cursors(t_env *env);

/*
**	@brief:	initialize the global environment struct
**
**	@param env	: global environment struct
**
**	the env struct is used to store data pointers and variables
**	detailing game state. in init_env this structure is allocated
**	and initialized.
*/
void					init_env(t_env **env);

/*
**	@brief: retrieve operation reference table
**
**	@param env	: global environment struct
**
**	load_optab receives a ptr to the global env struct and
**	loads the operation reference table into its op_tab variable
*/
void					load_optab(t_env *env);

/*
**	load_player takes a ptr to the main environment struct and
**	a player number, and loads the player with that number into
**	the allocated memory area at env->map. The player number is also
**	set in env->player_pos at the loaded memory area to keep track of player
**	positions.
*/
void					load_players(t_env *env);

/*
**	@brief:	parse and interpret program parameters
**
**	@param arg_nb	:	number of parameters
**	@param argv		:	parameters
**	@param env		:	global environment struct
**
**	parse_args iterates through the parameters passed to the program
**	and performs action based on the type of the parameter.
**
**	->	if the parameter is a flag, the related bit in the flag byte
**		is turned on. for the '-dump' and '-v' flag, the parameter
**		directly after the flag is saved as either the dump cycle
**		or the verbosity level.
**
**	->	otherwise, the parameter is assumed to be a player file
**		and is processed with add_player.
**
**	->	if the number of players is higher than MAX_PLAYERS or
**		if there are no players, the program exits with error.
**
**	lastly, valid_flags gets called to make sure there are
**	contradicting flags turned on.
*/
void					parse_args(int arg_nb, char **argv, t_env *env);

/*
**	program execution
*/

/*
**	@brief:	print the winning player to stdout
**
**	@param env		:	global environment struct
**
**	announce_winner gets called after the corewar main
**	process is finished. It retrieves the id of the last
**	player alive and prints a message, declaring the winner.
*/
void					announce_winner(t_env *env);

/*
**	@brief:	perform a periodic 'check' during the main corewar process.
**
**	@param env	:	gloval environment struct
**
**	check_corewar gets called every CYCLE_TO_DIE cycles to evaluate the
**	state of the game at the current cycle. Based on the game state, several
**	things can happen during the check:
**
**	->	for each cursor in the cursor stack, if it is dead, it is removed from the stack.
**
**	->	if during the last CYCLE_TO_DIE cycles, live was performed more than NBR_LIVES,
**		CYCLE_TO_DIE is reduced by CYCLE_DELTA.
**
**	->	if during the last CYCLE_TO_DIE cycles, live was performed less than NBR_LIVES,
**		compare the env->checks_counter to MAX_CHECKS. if more than MAX_CHECKS were performed,
**		CYCLE_TO_DIE is reduced by CYCLE_DELTA.
*/
void					check_corewar(t_env *env);

/*
**	@brief:	run the main corewar process
**
**	@param env	:	global environment structure
**
**	exec_corewar runs the programs main process. The process continues
**	as long as there are active cursors in the cursor stack and
**	env->cycles_to_die is higher or equal to zero. The main process
**	consists of several parts:
**
**	->	check which flags are enabled in check_flags.
**	->	process each cursor in exec_cursor_stack.
**	->	if CYCLE_TO_DIE is 0, run a check each cycle. The check is described
**		in check_corewar.c
**
**	once CYCLE_TO_DIE cycles have been processed, the current iteration ends
**	and a check occurs in check_corewar. Afterwards, exec_corewar gets
**	called recursively for the next iteration.
**
**	note: 	Over the course of the game, CYCLE_TO_DIE will continue to get
**			smaller, which gives cursors less time to send a live signal. This means that,
**			the longer the game continues, the harder it becomes for cursors to stay alive.
**
**	the last player to send a valid live signal wins the game.
*/
void					exec_corewar(t_env *env);

/*
**	@brief:	free the global environment struct
**
**	@param env	:	global environment struct
**
**	once the main process has finished, free_env is called
**	to clean up remaining allocated memory in the env struct.
*/
void					free_env(t_env **env);

/*
**	@brief:	introduce the players on stdout
**
**	@param env	: global environment struct
**
**	for each player, a message is printed to stdout,
**	with the name, size and number of the player.
*/
void					intro_players(t_env *env);

/*
**	move_cursor receives a cursor and moves the position
**	to the next operation. If the -v 16 flag is enabled,
**	the operation details are printed to stdout.
*/
void					move_cursor(t_cursor *cursor, t_env *env);

/*
**	move_cursor_encode is an alternative version of move_cursor
**	that gets called in operations that have a valid encoding byte.
*/
void					move_cursor_encode(t_cursor *cursor, t_env *env,
						unsigned char encode, unsigned char op_code);

/*
**	set_carry sets the carry flag of the cursor
**	passed as argument, depending on the mode provided.
**	if mode == 0, carry is set to 1.
**	if mode != 0, carry is set to 0.
*/
void					set_carry(t_cursor *cursor, int mode);

/*
**	validate_encode receives the encode byte of an operation and
**	checks if that encode byte is valid. returns 1 if valid and
**	returns 0 if the encode byte is invalid.
*/
int						valid_encode(BYTE op_code, BYTE encode, t_env *env);

/*
**	operation functions
*/

/*
**	invalid_op gets called when the cursor found a valid op_code
**	but its parameters were invalid. In this case, the cursor
**	is moved to the next operation. However, the cursor cannot
**	move more bytes than the max amount of bytes of the paremeters
**	if the op_code were valid.
*/
void					invalid_op(t_cursor *cursor, t_env *env, int type);

/*
**	op_add executes the operation add at the current
**	position of the cursor. It receives 3 T_REGS,
**	and stores the sum of the values in reg 1 and 2
**	in reg 3.
*/
void					op_add(t_cursor *cursor, t_env *env);

/*
**	op_and executes the operation and at the current
**	position of the cursor.
*/
void					op_and(t_cursor *cursor, t_env *env);

/*
**
*/
void					op_fork(t_cursor *cursor, t_env *env);

/*
**	op_ld executes the operation ld at the current position of the cursor.
**	if the first argument is a T_DIR, the value stored within this T_DIR
**	is written into the cursor registry at the number stored as the second
**	argument T_REG.
**
**	Otherwise, if the first argument is a T_IND, it represents a relative address.
**	It then reads the value stored at the address calculated by:
**
**	cursor->position + (FIRST_ARGUMENT % IDX_MOD);
**
**	and writes this value into cursor registry with the number stored as the second
**	argument T_REG.
**
**	If the value written is 0, the carry flag in the cursor is set to 1. Otherwise,
**	if the value written is !0, the carry flag is set to 0.
*/
void					op_ld(t_cursor *cursor, t_env *env);

/*
**
*/
void					op_ldi(t_cursor *cursor, t_env *env);

/*
**
*/
void					op_lfork(t_cursor *cursor, t_env *env);

/*
**	op_live executes operation live at the current position of the cursor,
**	if the negated player_number stored in the first registry is equal to
**	the argument T_DIR of the live operation. Otherwise, the live operation
**	is not executed.
**
**	live is reported in the following ways:
**
**	- cursor->last_live is set to the current program cycle.
**	- env->player_last_alive is set to the actual player number.
**	- the env->live_counter for the current CYCLE_TO_DIE iteration is incremented.
*/
void					op_live(t_cursor	*cursor, t_env *env);

/*
**
*/
void					op_lld(t_cursor *cursor, t_env *env);

/*
**
*/
void					op_lldi(t_cursor *cursor, t_env *env);

/*
**	op_or executes the operation op_or at the
**	current position of the cursor.
*/
void					op_or(t_cursor *cursor, t_env *env);

/*
**
*/
void					op_st(t_cursor *cursor, t_env *env);

/*
**	op_sti executes the operation sti at the current position
**	of the cursor passed as parameter. It receives a register number
**	as first argument, and writes the value stored in that register
**	to the relative address calculated as a result of:
**
**	cursor->position + (SECOND_ARGUMENT + THIRD_ARGUMENT % IDX_MOD);
**
**	if the encoding byte or the register numbers are invalid, the function
**	moves the cursor to the next operation by calling move_cursor.
*/
void					op_sti(t_cursor *cursor, t_env *env);

/*
**	op_sub executes the instruction op_sub at the
**	current position of the cursor.
*/
void					op_sub(t_cursor *cursor, t_env *env);

/*
**	op_xor executes the operation op_xor at the current
**	position of the cursor.
*/
void					op_xor(t_cursor *cursor, t_env *env);

/*
**	op_zjmp changes the position of the cursor according
**	to the relative address provided as operation argument, only
**	if cursor->carry == 1. if cursor->carry == 0,
**	zjmp does not execute but instead the cursor is moved to
**	the next operation.
*/
void					op_zjmp(t_cursor	*cursor, t_env *env);

/*
**	utility
*/

/*
**	count_registers receives an encoding byte and
**	counts how many arguments are T_REG.
*/
int						count_registers(unsigned char encode);

/*
**
*/
void					cpy_reg_vals(t_cursor *dst, t_cursor *src);

/*
**
*/
t_cursor				*dup_cursor(t_cursor *src, t_env *env);

/*
**
*/
int						get_arg(t_cursor *cursor, t_env *env, unsigned char encode, int arg_num);

/*
**	get_arg receives 2 bits and interprets them as a bitpair
**	of an encoding byte. It then returns the size related
**	to the argument type specified by the bitpair.
*/
unsigned char			get_arg_size(int op_code, int one, int two);

/*
**	get_bit returns the bit (0 or 1) at the index within octet.
**	If the index is not within byte-range, the function returns -1.
*/
int						get_bit(unsigned char octet, int index);

/*
**
*/
int						get_reg_num(t_cursor *cursor, t_env *env, unsigned char encode, int arg_num);

/*
**	read and return a T_DIR value from memory
*/
int						get_tdir(t_env *env, int position);

/*
**	T_DIR can have a different size in bytes depending
**	on the operation that uses it. By calling get_tdir_size with the
**	op_code, this function returns the correct T_DIR size in bytes.
**	return value is either 2 or 4 if correct, 0 if error.
*/
int						get_tdir_size(int opcode);

/*
**	read and return a T_IND value from memory
*/
short					get_tind(t_env *env, int position);

/*
**	get_total_arg_size receives an encoding byte, and returns
**	the combined size of all arguments noted in the encoding byte.
*/
unsigned char			get_total_arg_size(unsigned char op_code, unsigned char encode);

/*
**
*/
int						get_type(unsigned char encode, int arg_num);

/*
**	has_encode receives an op_code and checks if that operation
**	has an encoding byte. If it does, the function returns 1,
**	otherwise it returns 0.
*/
int						has_encode(unsigned char op_code);

/*
**	init_registries initialized the 16 registries of
**	a new cursor. Each cursor receives REG_NUMBER registries
**	of REG_SIZE. (16 registries of 4 bytes);
*/
int						*init_registries(void);

/*
**	modi receives a cursor index and if that cursor index
**	exceeds the memory map, returns the correct index
**	in circular memory. produces error if the provided
**	index is higher than MEM_SIZE * 2.
*/
unsigned int			modi(int index);

/*
**	push_cursor takes a cursor and pushes that cursor on the top
**	of the existing cursor stack.
*/
void					push_cursor(t_cursor *c, t_cursor **stack);

/*
**	reverse the endianness of a 4-byte number
*/
unsigned int			rev_endian(unsigned int oct);

/*
**	to_2bytes takes two bytes and returns them in their
**	two byte representation in a short.
*/
short					to_2bytes(unsigned char one, unsigned char two);

/*
**	to_4bytes takes two shorts (2 bytes) and returns them
**	in their 4 byte representation. (int)
*/
int						to_4bytes(unsigned short one, unsigned short two);

/*
**	valid_regs checks each argument and if it is a T_REG,
**	checks if the value contained is a valid register number.
*/
int						valid_regs(t_cursor *cursor, t_env *env, unsigned char encode);

/*
**	write_bytes receives a value and writes that value onto the
**	memory map at the position calculated by:
**
**	modi(cursor->position + rel_pos);
*/
void					write_bytes(int target_val, t_env *env, t_cursor *c, int rel_pos);

/*
**	printing
*/

/*
**	open .cor file and print header + execution code
*/
void					dump_champ_code(t_player *player, t_env *env);

/*
**	dump_cursor_stack receives a ptr to the cursor_stack
**	and prints the variables of each cursor to stdout.
*/
void					dump_cursor_stack(t_cursor *cursor_stack);

/*
**	dump_env_state prints the variables of env to stdout.
*/
void					dump_env_state(t_env *env);

/*
**	dump_prog_code takes a ptr to the champions execution code (exec) and
**	prints its instructions to stdout.
*/
void					dump_exec_code(char *exec_code, unsigned int prog_size, t_env *env);

/*
**	print header to stdout
*/
void					dump_header(header_t header);

/*
**	dump_mem prints the current state of the memory map
**	to stdout.
*/
void					dump_mem(t_env *env);

/*
**	dump_op prints a performed operation to stdout
**	if the -v 16 flag is enabled.
*/
void					dump_op(t_cursor *cursor, t_env *env);

/*
**	dump_op_encode is an alternative version of dump_op
**	that is used with operations that have encoding bytes.
**	encoding byte and op_code are passed manually, because the
**	the cursor state might be overwritten by the execution of the
**	the last operation.
*/
void					dump_op_encode(t_cursor *cursor, t_env *env, unsigned char encode, unsigned char op_code);

/*
**	dump_op_invalid is an alternative version of dump_op that gets
**	called when an operation was found to be invalid.
*/
void					dump_op_invalid(t_cursor *cursor, t_env *env, unsigned char bytes);

/*
**	dump_players takes a ptr to a list of players and
**	prints the header and execution code of each player
**	using dump_champ_code.
*/
void					dump_players(t_list *players, t_env *env);

/*
**
*/
void					dump_pos(t_env *env);

/*
**	print_bits prints octet in binary to stdout.
*/
void					print_bits(unsigned char octet);

/*
**	prints the name of operation currently stored in
**	the op_table, based on the given op_code.
*/
void					print_op_name(int op_code, t_env *env);

/*
**	error handlers
*/

/*
**	error_exec is the default error handler for the corewar program
**	execution cycle.
*/
void					error_exec(int err_code);

/*
**	error_init is the default error handler for errors related
**	to setting up the initial game state.
*/
void					error_init(int err_code);

/*
**	error_input is the default error handler for errors related
**	to input parsing.
*/
void					error_input(int err_code);

/*
**	error_mem is the default error handler for memory allocation
**	errors.
*/
void					error_mem();

/*
**	exit_usage prints program usage to stdout and exits the program.
*/
void					exit_usage();

/*
**	visualizer
*/

/*
**
*/
void					init_ncurses(t_env *env);

/*
**
*/
void					print_map(t_env *env);

void					process_flag(char **argv, int *i, int arg_nb, t_env *env);

#endif

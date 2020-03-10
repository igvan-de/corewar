/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_player.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 13:15:19 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/21 13:15:20 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	init_exece_code allocates memory for the exec_code variable
**	of the new t_player struct.
*/

static	void	init_exec_code(t_player **player, size_t size)
{
	(*player)->exec_code = ft_strnew(size);
	if (!((*player)->exec_code))
		error_mem();
}

/*
**	init_header allocates memory for the header_t variable
**	of the new t_player struct.
*/

static	void	init_header(header_t **header)
{
	(*header) = (header_t *)malloc(sizeof(header_t));
	if (!*header)
		error_mem();
}

/*
**	init_player allocates memory for the t_player struct
**	of the new player.
*/

static	void	init_player(t_player **player)
{
	(*player) = (t_player *)malloc(sizeof(t_player));
	if (!*player)
		error_mem();
	(*player)->nbr = 0;
	(*player)->exec_code = NULL;
	init_header(&((*player)->header));
}

/*
**	store_player takes a reference to a newly created player and stores
**	this pointer in the players list of the main env struct as a new list
**	element.
*/

static	void	store_player(t_player **new_player, t_env *env)
{
	t_list			*player_elem;

	(*new_player)->nbr = env->total_players + 1;
	player_elem = (t_list *)malloc(sizeof(t_list));
	if (!player_elem)
		error_mem();
	player_elem->content = *new_player;
	player_elem->content_size = sizeof(t_player *);
	player_elem->next = NULL;
	if (env->players == NULL)
		env->players = player_elem;
	else
		ft_lstaddend(&env->players, player_elem);
	env->total_players++;
}

/*
**	add_player takes a ptr to a program argument (arg) and parses
**	this argument as a player. A new t_player struct is created,
**	with the header stored in player->header and the execution_code
**	in player->exec_code. The player is also given a number and a color.
**	If the given argument is not a valid player, the function returns error.
**	The new player is stored within the players list in the main env struct at
**	env->players.
*/

void			add_player(char *arg, t_env *env)
{
	int				fd;
	ssize_t			bytes;
	t_player		*new_player;
	unsigned int	exec_code_size;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		error_input(1);
	init_player(&new_player);
	bytes = read(fd, new_player->header, sizeof(header_t));
	if (bytes != sizeof(header_t))
		error_input(2);
	if (rev_endian(new_player->header->magic) != COREWAR_EXEC_MAGIC)
		error_input(3);
	exec_code_size = rev_endian(new_player->header->prog_size);
	init_exec_code(&new_player, exec_code_size);
	bytes = read(fd, new_player->exec_code, exec_code_size);
	if (bytes != exec_code_size)
		error_input(4);
	close(fd);
	store_player(&new_player, env);
}

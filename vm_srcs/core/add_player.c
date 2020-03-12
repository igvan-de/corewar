/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_player.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 13:15:19 by jdunnink       #+#    #+#                */
/*   Updated: 2020/03/11 16:07:03 by ygroenev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	@brief:	initialize the players' execution code as a char *
**
**	@param player		:	ptr to t_player struct
**	@param size 		:	execution code size
**
**	init_exec_code allocates memory for the exec_code variable
**	of the new t_player struct.
*/

static	void	init_exec_code(t_player **player, size_t size)
{
	(*player)->exec_code = ft_strnew(size);
	if (!((*player)->exec_code))
		error_mem();
}

/**
**	@brief:	initialize a new header_t struct
**
**	@param header		:	ptr to the new header
**
**	init_header allocates memory for the header_t variable
**	of the new t_player struct.
*/

static	void	init_header(header_t **header)
{
	(*header) = (header_t *)malloc(sizeof(header_t));
	if (!*header)
		error_mem();
}

/**
**	@brief:	initialize a new t_player struct.
**
**	@param player		: ptr to the new player
**
**	init_player receives a ptr to an unallocated
**	player struct and allocates memory for that struct
**	as well as its header variable as player->header.
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

/**
**	@brief: store the new corewar player in the players list
**
**	@param new_player	:	new player struct
**	@param env			:	global environment struct
**
**	store_player receives a ptr to a new player struct and
**	stores that struct in a t_list node. It then adds that node
**	to the end of the current players list.
**	The players list is a t_list and is part of the env struct as env->players.
*/

static	void	store_player(t_player **new_player, t_env *env)
{
	t_list			*player_elem;

	(*new_player)->nbr = env->player_nbr;
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
	if (env->player_nbr == env->total_players)
		env->player_nbr = env->total_players + 1;
	else
		env->player_nbr = env->total_players;
}

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
	if (bytes > CHAMP_MAX_SIZE)
		error_input(12);
	close(fd);
	store_player(&new_player, env);
}

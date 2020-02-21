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

static	void	get_color(t_player *player)
{
	if (player->nbr == 1)
		player->color = ft_strdup(ANSI_COLOR_RED);
	else if (player->nbr == 2)
		player->color = ft_strdup(ANSI_COLOR_GREEN);
	else if (player->nbr == 3)
		player->color = ft_strdup(ANSI_COLOR_MAGENTA);
	else if (player->nbr == 4)
		player->color = ft_strdup(ANSI_COLOR_CYAN);
	else if (player->nbr == 5)
		player->color = ft_strdup(ANSI_COLOR_YELLOW);
	else if (player->nbr == 6)
		player->color = ft_strdup(ANSI_COLOR_BLUE);
	else
		error_init(1);
}


static	void	init_exec_code(t_player **player, size_t size)
{
	(*player)->exec_code = ft_strnew(size);
	if (!((*player)->exec_code))
		error_mem();
}

static	void	init_header(header_t **header)
{
	(*header)= (header_t *)malloc(sizeof(header_t));
	if (!*header)
		error_mem();
}

static	void	init_player(t_player **player)
{
	(*player) = (t_player *)malloc(sizeof(t_player));
	if (!*player)
		error_mem();
	(*player)->nbr = 0;
	(*player)->exec_code = NULL;
	(*player)->color	= NULL;
	init_header(&((*player)->header));
}

static	void	store_player(t_player **new_player, t_env *env)
{
	t_list			*player_elem;

	(*new_player)->nbr = env->total_players + 1;
	get_color(*new_player);
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

void	add_player(char *player, t_env *env)
{
	int				fd;
	ssize_t			bytes;
	t_player		*new_player;
	
	unsigned int	exec_code_size;

	fd = open(player, O_RDONLY);
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

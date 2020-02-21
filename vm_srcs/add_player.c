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
	(*player)->player_nb = 0;
	(*player)->exec_code = NULL;
	init_header(&((*player)->header));
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
	env->player = new_player;
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_s_file.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 13:01:21 by igor          #+#    #+#                 */
/*   Updated: 2020/04/29 15:18:17 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

static void write_name(int fd, header_t *header)
{
	ft_putstr_fd(".name: ", fd);
	ft_putstr_fd(header->prog_name, fd);
	ft_putstr_fd("\n", fd);
}

static void write_comment(int fd, header_t *header)
{
	ft_putstr_fd(".comment: ", fd);
	ft_putstr_fd(header->comment, fd);
	ft_putstr_fd("\n", fd);
}

void	write_s_file(int fd, header_t *header)
{
	write_name(fd, header);
	write_comment(fd, header);
}

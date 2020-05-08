/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_s_file.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 13:01:21 by igor          #+#    #+#                 */
/*   Updated: 2020/05/02 17:13:09 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

/*
** @brief writes name into filediscriptor in correct format
**
** @param fd	= filediscripter to write content into
** @param header = is struct containing all data of header
*/

static	void	write_name(int fd_s, t_header *header)
{
	ft_putstr_fd(".name ", fd_s);
	ft_putchar_fd('\"', fd_s);
	ft_putstr_fd(header->prog_name, fd_s);
	ft_putchar_fd('\"', fd_s);
	ft_putstr_fd("\n", fd_s);
}

/*
** @brief writes comment into filediscriptor in correct format
**
** @param fd	= filediscripter to write content into
** @param header = is struct containing all data of header
*/

static	void	write_comment(int fd_s, t_header *header)
{
	ft_putstr_fd(".comment ", fd_s);
	ft_putchar_fd('\"', fd_s);
	ft_putstr_fd(header->comment, fd_s);
	ft_putchar_fd('\"', fd_s);
	ft_putstr_fd("\n\n", fd_s);
}

/*
** @brief is the main function who moves through different functions to write
** all needed data in filediscripter (.s file)
**
** @param fd	= filediscripter to write content into
** @param file  = struct containing all needed data
*/

void			write_s_file(int fd_s, t_file *file)
{
	write_name(fd_s, file->header);
	write_comment(fd_s, file->header);
	write_args_into_s(fd_s, rev_endian(file->header->prog_size), file);
}

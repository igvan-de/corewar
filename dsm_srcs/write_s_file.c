/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_s_file.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 13:01:21 by igor          #+#    #+#                 */
/*   Updated: 2020/05/01 18:11:35 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

/*
* @brief writes name into filediscriptor in correct format
*
* @param fd	= filediscripter to write content into
* @param header = is struct containing all data of header
*/

static void write_name(int fd, header_t *header)
{
	ft_putstr_fd(".name: ", fd);
	ft_putchar_fd('\"', fd);
	ft_putstr_fd(header->prog_name, fd);
	ft_putchar_fd('\"', fd);
	ft_putstr_fd("\n", fd);
}

/*
* @brief writes comment into filediscriptor in correct format
*
* @param fd	= filediscripter to write content into
* @param header = is struct containing all data of header
*/

static void write_comment(int fd, header_t *header)
{
	ft_putstr_fd(".comment: ", fd);
	ft_putchar_fd('\"', fd);
	ft_putstr_fd(header->comment, fd);
	ft_putchar_fd('\"', fd);
	ft_putstr_fd("\n\n", fd);
}

/*
* @brief is the main function who moves through different functions to write
* all needed data in filediscripter (.s file)
*
* @param fd	= filediscripter to write content into
* @param file  = struct containing all needed data
*/

void	write_s_file(int fd, t_file *file)
{
	write_name(fd, file->header);
	write_comment(fd, file->header);
	write_arg_s(fd, rev_endian(file->header->prog_size), file);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_champ_code.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 14:51:53 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/20 14:51:53 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	open .cor file and print header + execution code
*/

void	dump_champ_code(char *champ, t_env *env)
{
	int			fd;
	ssize_t		bytes;
	header_t	header;
	char		*exec_code;

	//	open .cor file
	fd = open(champ, O_RDONLY);
	printf("	opened %s at fd: %i\n", champ, fd);


	// read and print header
	bytes = read(fd, &header, sizeof(header_t));
	printf("		bytes read into header: %li / should be: %li\n", bytes, sizeof(header_t));
	dump_header(header);


	// read and print execution code
	exec_code = ft_strnew(rev_endian(header.prog_size));
	bytes = read(fd, exec_code, rev_endian(header.prog_size));
	if (bytes != rev_endian(header.prog_size))
		ft_putendl("	error: actual size does not match header prog_size");
	printf("	execution code size:		%li\n", bytes);
	dump_exec_code(exec_code, rev_endian(header.prog_size), env);


	// close .core file
	close(fd);
	ft_putchar('\n');
}

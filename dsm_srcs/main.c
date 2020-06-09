/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:31:32 by igor          #+#    #+#                 */
/*   Updated: 2020/06/08 15:27:23 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

/*
** @brief mallocs header struct
**
** @param header = pointer to header struct
*/

static	void	init_header(t_header **header)
{
	(*header) = (t_header *)malloc(sizeof(t_header));
	if (*header == NULL)
	{
		ft_printf("No header has been found\n");
		exit(1);
	}
}

/*
** @brief mallocs file struct and pointer to header struct
**
** @param file
*/

static	void	init_file(t_file **file)
{
	*file = (t_file*)ft_memalloc(sizeof(t_file));
	load_optab_file(*file);
	init_header(&((*file)->header));
}

/*
** @brief checks if bytes has the correct size value
**
** @param bytes = bytes readed
** @param file = struct containing data prog_size
*/

static	void	error_check(ssize_t bytes, unsigned int exec_code_size)
{
	if (bytes != exec_code_size)
	{
		ft_printf("Amount of bytes isn't equal to exec_code_size\n");
		exit(1);
	}
	if (bytes > CHAMP_MAX_SIZE)
	{
		ft_printf("Amount of bytes isn't bigger then max champ size\n");
		exit(1);
	}
}

/*
** @brief initializes a empty string
**
** @param file = struct with needed data
** @param size = size for mallocing new string
*/

static	void	init_exec_code(t_file **file, size_t size)
{
	(*file)->exec = ft_strnew(size);
	if (!((*file)->exec))
	{
		ft_printf("Couldn't initialize new string in init_exec_code\n");
		exit(1);
	}
}

/*
** @brief read given .cor file and transforms all content into a humanreadable
** assembly file (.s file)
**
** @param argc = arguments counter
** @param argv = arguments
** @return int = return value if program run succesfully
*/

int				main(int argc, char **argv)
{
	t_mainvars v;

	if (argc < 2)
		return (1);
	v.fd_name = file_check(argv[1]);
	v.fd_cor = open(argv[1], O_RDONLY);
	init_file(&v.file);
	v.bytes = read(v.fd_cor, v.file->header, sizeof(t_header));
	if (v.bytes != sizeof(t_header))
		exit(1);
	v.fd_s = open(v.fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0640);
	v.exec_code_size = rev_endian(v.file->header->prog_size);
	init_exec_code(&v.file, v.exec_code_size);
	v.bytes = read(v.fd_cor, v.file->exec, v.exec_code_size);
	error_check(v.bytes, v.exec_code_size);
	write_s_file(v.fd_s, v.file);
	close(v.fd_cor);
	close(v.fd_s);
	free_vars(&v);
	return (0);
}

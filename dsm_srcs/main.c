/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:31:32 by igor          #+#    #+#                 */
/*   Updated: 2020/05/01 11:44:30 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

/*
* @brief file_check first splits the given arguments on '.' character,
* afterwards it checks if the given file is an .cor file.
*
*
* @param argv = the complete argument which contains the name of file
* @return char* = the .s filename
*/

static char	*file_check(char *argv)
{
	char	**name;
	char	*fd_name;
	int		i;

	i = 0;
	name = ft_strsplit(argv, '.');
	while (name[i] != NULL)
		i++;
	if (ft_strequ(name[i - 1], "cor") == 0)
	{
		ft_printf("Error, wrong file. Needs to be a .cor file\n");
		exit(-1);
	}
	fd_name = ft_strjoin(name[0], ".s-dsm");
	free_split(name);
	return(fd_name);
}

/*
* @brief mallocs header struct
*
* @param header = pointer to header struct
*/

static	void	init_header(header_t **header)
{
	(*header) = (header_t *)malloc(sizeof(header_t));
	if (*header == NULL)
		exit(-1);
}

/*
* @brief mallocs file struct and pointer to header struct
*
* @param file
*/

static void	init_file(t_file **file)
{
	*file = (t_file*)ft_memalloc(sizeof(t_file));
	load_optab_file(*file);
	init_header(&((*file)->header));
}

/*
* @brief checks if bytes has the correct size value
*
* @param bytes = bytes readed
* @param file = struct containing data prog_size
*/

static void	error_check(ssize_t bytes, unsigned int exec_code_size)
{
	if (bytes != exec_code_size)
		exit(-1); //need to make correct error message
	if (bytes > CHAMP_MAX_SIZE)
		exit(-1); //need to make correct error message
}

static	void	init_exec_code(t_file **file, size_t size)
{
	(*file)->exec_code = ft_strnew(size);
	if (!((*file)->exec_code))
		exit(-1); //need to make correct error message
}

/*
* @brief read given .cor file and transforms all content into a humanreadable
* assembly file (.s file)
*
* @param argc = arguments counter
* @param argv = arguments
* @return int = return value if program run succesfully
*/

int	main(int argc, char **argv)
{
	char	*fd_name;
	int		new_fd;
	int		fd;
	ssize_t	bytes;
	t_file	*file;
	unsigned int	exec_code_size;

	if (argc < 1)
		return(-1);
	fd_name = file_check(argv[1]);
	new_fd = open(fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0640); //O_TRUNC to overwrite existing .s file
	fd = open(argv[1], O_RDONLY);
	init_file(&file);
	bytes = read(fd, file->header, sizeof(header_t));
	if (bytes != sizeof(header_t))
		exit(-1); //need to make correct error message
	exec_code_size = rev_endian(file->header->prog_size);
	init_exec_code(&file, exec_code_size);
	bytes = read(fd, file->exec_code, exec_code_size);
	error_check(bytes, exec_code_size);
	write_s_file(new_fd, file);
	close(fd);
	return(0);
}

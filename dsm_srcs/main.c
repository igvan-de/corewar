/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: igor <igor@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:31:32 by igor          #+#    #+#                 */
/*   Updated: 2020/04/29 15:16:55 by igor          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "dsm.h"

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
	// free_split(name); //|| has error because need to include it from asm.h
	return(fd_name);
}

static	void	init_header(header_t **header)
{
	(*header) = (header_t *)malloc(sizeof(header_t));
	if (*header == NULL)
		exit(-1);
}

static void	init_file(t_test **file)
{
	*file = (t_test*)ft_memalloc(sizeof(t_test));
	init_header(&((*file)->header));
}

int	main(int argc, char **argv)
{
	char	*fd_name;
	int		new_fd;
	int		fd;
	ssize_t	bytes;
	t_test	*file;

	if(argc < 1)
		return(-1);
	fd_name = file_check(argv[1]);
	new_fd = open(fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0640); //O_TRUNC to overwrite existing .s file
	fd = open(argv[1], O_RDONLY);
	init_file(&file);
	bytes = read(fd, file->header, sizeof(header_t));
	if (bytes == -1)
		exit(-1);
	write_s_file(new_fd, file->header);
	return(0);
}

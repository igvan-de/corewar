/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 08:46:02 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/18 08:46:39 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

//	reverse endian

unsigned int little_big(unsigned int little)
{
    return((little&0xff)<<24)+((little&0xff00)<<8)+((little&0xff0000)>>8)+      \
                                                             ((little>>24)&0xff);
}

//	print header to stdout

static	void	dump_header(header_t header)
{
	printf("	header has magic: %#0x\n", header.magic);
	if (header.magic == COREWAR_EXEC_MAGIC)
		printf("	---> magic is valid!\n");
	else
		printf("	---> error: magic is invalid!\n");
	printf("	header has name:	%s\n", header.prog_name);
	printf("	header has prog size: %#0x\n", header.prog_size);
	printf("	header has comment: %s\n", header.comment);
}

//	open argument and read the first 2192 bytes into a header struct

static	void	parse_header(char *arg)
{
	int			fd;
	ssize_t		bytes;
	header_t	header;

	fd = open(arg, O_RDONLY);
	printf("	opened file %s at fd: %i in parse_header\n", arg, fd);
	bytes = read(fd, &header, sizeof(header_t));
	header.magic = little_big(header.magic);
	header.prog_size = little_big(header.prog_size);
	printf("		bytes read into header: %li\n", bytes);
	dump_header(header);
}

//	parse all arguments

static	void	parse_args(int arg_nb, char **argv)
{
	int i;

	printf("	parse args is called with %i arguments\n\n\n", arg_nb - 1);

	i = 1;
	while (i < arg_nb)
	{
		parse_header(argv[i]);
		ft_putchar('\n');
		i++;
	}
}

//	main entry for corewar

int main(int argc, char **argv)
{
	ft_putstr("\n\n<------------------------- Welcome to Corewar! ---------------------->\n\n\n");

	parse_args(argc, argv);
	return (0);
}

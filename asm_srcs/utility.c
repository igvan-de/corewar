/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/29 09:59:56 by mlokhors       #+#    #+#                */
/*   Updated: 2020/04/03 09:51:27 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_end_line(t_func_list *list)
{
	while (list->line[list->line_char] && ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	if (list->line_number == 13)
		ft_printf("24str %s \nchar %c \nnumber char %d\n\n", list->line, list->line[list->line_char], list->line_char);
	if (list->line[list->line_char] && list->line[list->line_char] != COMMENT_CHAR)
	{
		error_message(list, 40, 0, 4);
	}
	if (list->line_number == 13)
		ft_printf("25str %s \nchar %c \nnumber char %d\n\n", list->line, list->line[list->line_char], list->line_char);
}

int			pm_atoi(t_func_list *list)
{
	int		nega;
	int	result;

	nega = 1;
	result = 0;
	while (list->line[list->line_char] && ft_isspace(list->line[list->line_char]) == 1)
		list->line_char++;
	if (list->line[list->line_char] == '+' || list->line[list->line_char] == '-')
	{
		if (list->line[list->line_char] == '-')
			nega = -1;
		list->line_char++;
	}
	while (list->line[list->line_char] >= '0' && list->line[list->line_char] <= '9')
	{
		result = result * 10 + list->line[list->line_char] - '0';
		list->line_char++;
	}
	return (nega * result);
}

bool		check_label_char(char c)
{
	int i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (c == LABEL_CHARS[i])
			return (true);
		i++;
	}
	return (false);
}


uint64_t    calc_hash(const void *bytes, size_t len)
{
    unsigned char    *p;
    uint64_t        hash;
    size_t            i;

    i = 0;
    hash = 14695981039346656037U;
    p = (unsigned char*)bytes;
    while (i < len)
    {
        hash = p[i] ^ (hash * 1099511628211U);
        i++;
    }
    return (hash);
}

/*
** @brief reverse the bytes by four
**
** @param oct = octal receiving
** @return unsigned	int
*/

unsigned int	rev_endian(unsigned int oct)
{
	return (((oct & 0xff) << 24) + ((oct & 0xff00) << 8) +
		((oct & 0xff0000) >> 8) + ((oct >> 24) & 0xff));
}

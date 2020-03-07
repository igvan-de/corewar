/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_color.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/22 13:51:55 by mark           #+#    #+#                */
/*   Updated: 2020/03/07 17:19:19 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_color(t_container *list, int number, int length)
{
	const char *colors[13] = {RED, BRED, GREEN, BGREEN,
	YELLOW, BYELLOW, BLUE, BBLUE, MAGENTA, BMAGENTA, CYAN,
	BCYAN, RESET
	};

	add_str(list, colors[number]);
	return (length);
}

static int	handle_b_blue(t_container *list, char *str)
{
	if (ft_strncmp(str, "{BRED}", 6) == 0)
		return (check_color(list, 1, 6));
	else if (ft_strncmp(str, "{BGREEN}", 8) == 0)
		return (check_color(list, 3, 8));
	else if (ft_strncmp(str, "{BYELLOW}", 9) == 0)
		return (check_color(list, 5, 9));
	else if (ft_strncmp(str, "{BBLUE}", 7) == 0)
		return (check_color(list, 7, 7));
	else if (ft_strncmp(str, "{BMAGENTA}", 9) == 0)
		return (check_color(list, 9, 9));
	else if (ft_strncmp(str, "{BCYAN}", 7) == 0)
		return (check_color(list, 11, 7));
	return (0);
}

int			handle_color(t_container *list, char *str)
{
	if (ft_strncmp(str, "{RED}", 5) == 0)
		return (check_color(list, 0, 5));
	else if (ft_strncmp(str, "{GREEN}", 7) == 0)
		return (check_color(list, 2, 7));
	else if (ft_strncmp(str, "{YELLOW}", 8) == 0)
		return (check_color(list, 4, 8));
	else if (ft_strncmp(str, "{BLUE}", 6) == 0)
		return (check_color(list, 6, 6));
	else if (ft_strncmp(str, "{MAGENTA}", 9) == 0)
		return (check_color(list, 8, 9));
	else if (ft_strncmp(str, "{CYAN}", 6) == 0)
		return (check_color(list, 10, 6));
	else if (ft_strncmp(str, "{RESET}", 7) == 0)
		return (check_color(list, 12, 7));
	else
		return (handle_b_blue(list, str));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_ncurses.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 16:08:26 by jdunnink      #+#    #+#                 */
/*   Updated: 2020/02/27 16:08:26 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_ncurses(t_env *env)
{
	initscr();
	start_color();
	use_default_colors();
	init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_WHITE, 999, 999, 999);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	print_map(env);
}

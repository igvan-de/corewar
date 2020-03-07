/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 03:27:37 by mlokhors       #+#    #+#                */
/*   Updated: 2020/03/07 17:15:02 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H
# include <string.h>

int						ft_isspace(int c);
int						ft_numlen_ull(unsigned long long nb, int base);
unsigned long long		ft_power(int x, int power);

#endif

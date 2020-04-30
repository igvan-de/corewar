/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 17:43:55 by igvan-de      #+#    #+#                 */
/*   Updated: 2020/04/30 17:44:36 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H
# include <string.h>

int						ft_isspace(int c);
int						ft_numlen_ull(unsigned long long nb, int base);
unsigned long long		ft_power(int x, int power);

#endif

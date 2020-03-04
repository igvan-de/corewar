/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlokhors <mlokhors@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 03:27:37 by mlokhors       #+#    #+#                */
/*   Updated: 2019/10/17 02:54:45 by mark          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H
# include <string.h>

int						ft_isspace(int c);
char					*ft_strcpy(char *dest, const char *src);
int						ft_atoi(const char *str);
unsigned long long		ft_power(int x, int power);
int						ft_numlen_ull(unsigned long long nb, int base);
char					*ft_strchr(const char *str, int ch);
int						ft_strncmp(const char *s1,
							const char *s2, size_t count);
char					*ft_strnew(size_t size);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s1);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);

#endif

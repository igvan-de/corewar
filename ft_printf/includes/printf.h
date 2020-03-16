/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdunnink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/14 09:30:42 by jdunnink      #+#    #+#                 */
/*   Updated: 2019/06/14 09:55:36 by jdunnink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 20

/*
**	main format specifier structure
*/

typedef struct	s_spec
{
	char		*flags;
	int			width;
	int			width_on;
	int			precis;
	int			prec_on;
	char		type;
	int			type_size;
}				t_spec;

/*
**	print functions
*/

int				ft_printf(const char *format, ...);
int				ft_asprintf(char **dest, const char *format, ...);
int				ft_vasprintf(char **d, const char *f, va_list a, int res);

/*
**	type handlers
*/

int				pf_handle_csp(char **arg, t_spec info, va_list a_list);
int				pf_handle_idu(char **tmp, t_spec info, va_list a_list);
int				pf_handle_x(char **tmp, t_spec info, va_list a_list);
int				pf_handle_f(char **tmp, t_spec info, va_list a_list);
int				pf_handle_o(char **tmp, t_spec info, va_list a_list);

/*
**	toascii converters
*/

char			*pf_toa_sign(long long val, int b, int type_size, int alph);
char			*pf_toa_unsign(unsigned long long val, int b, int t, int a);
char			*ft_ptoa(void *pointer, int base);
char			*pf_dtoa(long double value, int precision);
char			*pf_ltoa(long int n);

/*
**	utility
*/

void			pf_round_ld(long double value, char **dest);
void			pf_flag_override(t_spec *format);
t_spec			*pf_get_specinfo(char **format, t_spec *info);

/*
**	general support functions
*/

char			*ft_strdup(const char *s1);
char			*ft_strndup(char *src, size_t nb);
char			*ft_strdup_exep(const char *s1, char c);
char			*ft_strdup_until(const char *s1, char end);
char			*ft_strnew(size_t size);
char			*ft_strnew_c(size_t len, char c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free(char *s1, char *s2, int mode);
char			*ft_stradd(char *target, char *add);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_str_tail(char *str);
int				ft_str_only(char *str, char c);
size_t			ft_strlen(const char *str);
size_t			ft_count_digits(char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_ctostr(char c);
int				ft_cinstr(const char *str, char c);
int				ft_count_cinstr(char *str, char c);
void			ft_putchar(char c);
void			ft_putstr(char *str);
int				ft_atoi(const char *str);
char			*ft_itoa_base(int value, int base);
long int		ft_labs(long int nb);
long long		ft_llabs(long long nb);
void			ft_move_sign(char *str);
int				ft_isspace(char c);
int				ft_issign(char c);
int				ft_isdigit(char c);

#endif

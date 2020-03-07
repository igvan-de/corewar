/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mark <mark@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/21 14:35:36 by mark           #+#    #+#                */
/*   Updated: 2020/03/07 17:18:27 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include "utility.h"
# include "libft.h"

# define HASH (1 << 0)
# define NUL (1 << 1)
# define MIN (1 << 2)
# define PLUS (1 << 3)
# define SPACE (1 << 4)
# define LEN_H (1 << 0)
# define LEN_HH (1 << 1)
# define LEN_L	(1 << 2)
# define LEN_LL (1 << 3)
# define LEN_FL (1 << 4)
# define BUFF_SIZE 1024
# define RED "\033[0;31m"
# define BRED "\033[1;31m"
# define GREEN "\033[0;32m"
# define BGREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define BYELLOW "\033[1;33m"
# define BLUE "\033[0;34m"
# define BBLUE "\033[1;34m"
# define MAGENTA "\033[0;35m"
# define BMAGENTA "\033[1;35m"
# define CYAN "\033[0;36m"
# define BCYAN "\033[1;36m"
# define RESET "\033[0m"

typedef enum			e_desc {
	E_CHAR = 0,
	E_STRING = 1,
	E_VOID_POINTER = 2,
	E_INT = 3,
	E_OCTAL = 4,
	E_HEX = 5,
	E_UHEX = 6,
	E_FLOAT = 7,
	E_UINT = 8,
	E_PERCENT = 9,
	E_BITS = 10,
	E_INVALID = -1
}						t_desc;

typedef struct			s_pair
{
	char				key;
	t_desc				desc;
}						t_pair;

typedef union			u_bits
{
	long long			sign;
	unsigned long long	notsign;
}						t_bits;

typedef struct			s_container
{
	va_list				ap;
	int					width;
	int					precision;
	int					flags;
	int					lengthmod;
	char				buff[BUFF_SIZE];
	int					i;
	int					con;
	int					dot;
	int					bit;
	int					fd;
	void				*str;
	int					total;
	void				(*writer)(struct s_container *list);
}						t_container;

typedef struct			s_float_str
{
	char				*str;
	int					length;
}						t_float_str;

typedef struct			s_whole_float
{
	unsigned long long	whole_num;
	long double			remaining;
	int					posi;
	int					nega;
	int					sign;
	int					lefttimes;
}						t_whole_float;

typedef struct			s_number
{
	unsigned long long	number;
	int					length;
	int					sign;
	int					base;

}						t_number;

void					add_sign(t_whole_float *number, t_container *list);
void					right_float_flags(t_container *list,
						int length_wholenum, t_whole_float *number);
int						o_check_zero(t_container *list, t_number number);
int						nanfin(t_container *list, long double number);
void					pre_check_binary(char **str, t_container *list);
typedef	void			(*t_print_var)(t_container *list);
int						make_print(t_container *list, char *str);
long double				decimal(long double remaining);
void					rounding(t_float_str *line, int after_precision);
void					ft_itoa_base_len_float(t_float_str *line,
						t_whole_float *wholenum, int length_wholenum, int side);
int						nanfin(t_container *list, long double number);
void					into_def(t_whole_float *number,
						long double decinum, int *length_wholenum,
						t_container *list);
void					writer_str(t_container *list);
void					writer_fd(t_container *list);
void					print_bits_str(t_container *list, t_bits sort);
void					rrmaining(t_container *list);
int						handle_color(t_container *list, char *str);
void					pre_itoa_pf_padding(t_container *list,
						t_number number, int letter_case);
void					right_padding_pre_zero(t_container *list,
						t_number number);
void					check_width_pf(t_container *list, t_number number);
int						get_amount_pf(t_container *list, t_number number);
void					f_percent(t_container *list);
void					f_uint(t_container *list);
int						check_sign(t_number *number, long long *i);
void					right_padding_int(t_container *list, t_number number);
void					left_padding_int(t_container *list, t_number number);
void					add_str(t_container *list, const char *str);
void					cast_itoa_pf_base(t_container *list,
						t_number *number);
void					right_padding_pf_base(t_container *list,
						t_number number, int letter_case);
void					left_padding_pf_base(t_container *list,
						t_number number, int letter_case);
void					check_flags(t_container *list, t_number number);
void					add_space(t_container *list, int amount);
void					add_zero(t_container *list, int amount);
void					addbuff(t_container *list, char c);
void					right_padding(char *str, t_container *list, int check);
void					left_padding(char *str, t_container *list, int check);
void					f_bits(t_container *list);
void					f_char(t_container *list);
void					f_float(t_container *list);
void					f_iint(t_container *list);
void					f_int(t_container *list);
void					f_void_pointer(t_container *list);
void					f_octal(t_container *list);
void					f_hex(t_container *list);
void					f_string(t_container *list);
void					f_uint(t_container *list);
void					check_flag(char **str, t_container *list);
void					check_widthprecision(char **str, t_container *list);
void					check_lenthmod(char **str, t_container *list);
void					empty(t_container *list);
void					ft_itoa_base_len(t_container *list,
						t_number number, int letter_case);
unsigned long long		ft_power(int x, int power);
int						ft_printf(char *str, ...);
int						ft_dprintf(int fd, char *format, ...);
int						ft_sprintf(char *str, char *format, ...);

#endif

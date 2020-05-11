# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jdunnink <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/03/20 09:33:47 by jdunnink       #+#    #+#                 #
#    Updated: 2020/03/16 21:22:41 by igvan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC =	pf_flag_override.c	\
		pf_get_specinfo.c	\
		pf_handle_csp.c		\
		pf_handle_idu.c		\
		pf_handle_x.c		\
		pf_handle_f.c		\
		pf_handle_o.c		\
		pf_toa_sign.c		\
		pf_toa_unsign.c		\
		pf_dtoa.c			\
		pf_ltoa.c			\
		pf_round_ld.c		\
		ft_printf.c			\
		ft_vasprintf.c		\
		ft_asprintf.c		\
		ft_isdigit.c		\
		ft_issign.c			\
		ft_atoi.c			\
		ft_cinstr.c			\
		ft_count_cinstr.c	\
		ft_count_digits.c	\
		ft_ctostr.c			\
		ft_isspace.c		\
		ft_itoa_base.c		\
		ft_labs.c			\
		ft_llabs.c			\
		ft_memset.c			\
		ft_move_sign.c		\
		ft_ptoa.c			\
		ft_putchar.c		\
		ft_putstr.c			\
		ft_str_only.c		\
		ft_str_tail.c		\
		ft_stradd.c			\
		ft_strcat.c			\
		ft_strcmp.c			\
		ft_strcpy.c			\
		ft_strdup_exep.c	\
		ft_strdup_until.c	\
		ft_strdup.c			\
		ft_strjoin_free.c	\
		ft_strjoin.c		\
		ft_strlen.c			\
		ft_strndup.c		\
		ft_strnew_c.c		\
		ft_strnew.c			\

OBJ = $(SRC:.c=.o)
SRCDIR = srcs
OBJDIR = objs

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

HEADER = -I includes/
cc = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(NAME):
	@/bin/mkdir -p $(OBJDIR)
	@$(CC) -c $(CFLAGS) $(SRCS) $(HEADER)
	@/bin/mv $(OBJ) $(OBJDIR)/
	@ar rcs $(NAME) $(OBJS)

clean:
	@/bin/rm -Rf $(OBJDIR)
	@/bin/rm -Rf *~ *#

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

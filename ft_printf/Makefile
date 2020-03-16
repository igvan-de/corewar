<<<<<<< HEAD
# **************************************************************************** #
=======
#******************************************************************************#
>>>>>>> master
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
<<<<<<< HEAD
#    By: mlokhors <mlokhors@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/29 09:57:34 by mlokhors       #+#    #+#                 #
#    Updated: 2020/03/07 17:28:14 by igvan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

COLOR_GREEN = $(shell printf "\e[38;5;10m")
COLOR_DEFAULT = $(shell printf "\e[39m")

NAME := libftprintf.a
UTI_DIR := ./utility/
PRT_DIR := ./
FLAGS := -Wall -Werror -Wextra -I .././includes
CC := gcc
PRINT_PLUS = $(shell printf '$(COLOR_GREEN)[ + ]$(COLOR_DEFAULT)')

UTI_SRC :=	 ft_power \
			 ft_numlen_ull \
			 ft_isspace \

PRT_SRC :=   handle_char \
			 handle_float \
			 handle_float2 \
			 handle_float3 \
			 handle_float4 \
			 handle_int \
			 handle_memory \
			 handle_octal \
			 handle_octal2 \
			 handle_octal3 \
			 handle_hex \
			 handle_str \
			 handle_uint \
			 handle_percent \
			 handle_color \
			 handle_bits \
			 handle_bits2 \
			 padding \
			 widthprecision \
			 listbuff \
			 ft_itoa_base_len \
			 flags \
			 print_version \
			 make_print

FILE_SRC := $(PRT_SRC:%=$(PRT_DIR)%.c) $(UTI_SRC:%=$(UTI_DIR)%.c)

OBJS := $(FILE_SRC:%.c=%.o)


all: $(NAME)

$(NAME) : $(OBJS)
		@ar crs $(NAME) $(OBJS)

%.o: %.c .././includes/ft_printf.h .././includes/utility.h
	@$(CC) $(FLAGS) -c -o $@ $< -I .././includes
	@echo "$(PRINT_PLUS) $@"

clean:
		@rm -rf $(OBJS)

fclean: clean
		@rm -f $(NAME)
=======
#    By: jdunnink <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/03/20 09:33:47 by jdunnink      #+#    #+#                  #
#    Updated: 2019/06/14 08:42:59 by jdunnink      ########   odam.nl          #
#                                                                              #
#******************************************************************************#

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
	/bin/mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $(SRCS) $(HEADER)
	/bin/mv $(OBJ) $(OBJDIR)/
	ar rcs $(NAME) $(OBJS)

clean:
	/bin/rm -Rf $(OBJDIR)
	/bin/rm -Rf *~ *#

fclean: clean
	/bin/rm -f $(NAME)
>>>>>>> master

re: fclean all

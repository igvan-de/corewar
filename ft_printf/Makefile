# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
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

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: igvan-de <igvan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/16 09:11:59 by igvan-de      #+#    #+#                  #
#    Updated: 2020/04/14 10:13:27 by igvan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include sources

include ../asm_srcs/sources
include ../asm_srcs/asm_to_byte/sources
# include ../asm_srcs/check_file/sources
include ../asm_srcs/error_functions/sources

OBJ_FILES = $(TESTSRCS:%.c=%.o)
ASM_SRCS_ = $(ASM_SRCS:%.c=../%.c)
OBJ_ASM = $(ASM_SRCS_:%.c=%.o)
INCLUDES = -I .././includes -I $(HOME)/.brew/include


NAME = unit_test_asm
CFLAGS = -Wall -Werror
CRITERION := -L $(HOME)/.brew/lib -lcriterion
LIB = .././libft/libft.a .././ft_printf/libftprintf.a
ASM = ../asm

COLOR_GREEN = $(shell printf "\e[38;5;10m")
COLOR_DEFAULT = $(shell printf "\e[39m")
PRINT_PLUS = $(shell printf '$(COLOR_GREEN)[ + ]$(COLOR_DEFAULT)')

all: $(NAME)
	@mv $(NAME) ../$(NAME)

%.o: %.c
	@gcc $< -c -o $@ $(CFLAGS) $(INCLUDES)
	@echo "$(PRINT_PLUS) $@"

$(NAME): $(ASM) $(OBJ_FILES)
	@gcc -coverage $(CRITERION) $(OBJ_ASM) $(OBJ_FILES) $(CFLAGS) $(LIB) -o $@

$(ASM): FORCE
	@Make -C ../

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f ../$(NAME)

re:
	@make fclean
	@make all

FORCE:

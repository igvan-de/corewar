# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: igvan-de <igvan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/18 17:58:55 by igvan-de       #+#    #+#                 #
#    Updated: 2020/03/07 17:21:17 by igvan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include asm_srcs/sources
include asm_srcs/error_functions/sources
include asm_srcs/asm_to_byte/sources

OBJ_ASM = $(SRCS:%.c=%.o)
LIBFT_H = -I ./libft/includes
ASM_H = -I ./includes
PRTF_H = -I ./ft_printf
NAME = asm
CFLAGS =  -Wall -Werror -Wextra
NORM = norminette $(SRCS) | grep -e "Error" -e "Warning" -B 1

COLOR_GREEN = $(shell printf "\e[38;5;10m")
COLOR_RED = $(shell printf "\e[31;5;10m")
COLOR_YELLOW = $(shell printf "\e[33;5;10m")
COLOR_DEFAULT = $(shell printf "\e[39m")
PRINT_PLUS = $(shell printf '$(COLOR_GREEN)[ + ]$(COLOR_DEFAULT)')
PRINT_CLEAN = $(shell printf '$(COLOR_RED)[ - ]$(COLOR_DEFAULT)')
PRINT_DONE = $(shell printf '$(COLOR_YELLOW)[ › ]$(COLOR_DEFAULT)')

all: $(NAME)

%.o: %.c includes/asm.h
	@gcc $< -c -o $@ $(CFLAGS) $(ASM_H) $(LIBFT_H) $(PRTF_H)
	@echo "$(PRINT_PLUS) $@"

asm: $(OBJ_ASM) libft/libft.a ft_printf/libftprintf.a
	@gcc $(CFLAGS) $(OBJ_ASM) libft/libft.a -o $@ ft_printf/libftprintf.a -o $@
	@echo "$(PRINT_DONE) Compiling asm completed"

libft/libft.a: FORCE
	@make -C libft/

ft_printf/libftprintf.a: FORCE
	@make -C ft_printf/

unit_test:
	@make -C unit_test/

clean:
	@rm -f $(OBJ_FILES)
	@make -C ./Libft clean
	@make -C ./ft_printf clean
	@echo "$(PRINT_CLEAN) Cleaning objectives completed"

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean
	@make -C ./ft_printf fclean
	@echo "$(PRINT_CLEAN) Cleaning all completed"

re:
	@make fclean
	@make all

norm:
	@echo "===================NORMINETTE==================="
	@$(NORM) || echo "no norminette errors"
	@echo "================================================"

FORCE:

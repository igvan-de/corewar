# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: igvan-de <igvan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/18 17:58:55 by igvan-de       #+#    #+#                 #
#    Updated: 2020/03/16 21:19:51 by igvan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include vm_srcs/sources
include asm_srcs/sources
include asm_srcs/error_functions/sources
include asm_srcs/asm_to_byte/sources
# include asm_srcs/check_file/sources


OBJ_ASM = $(ASM_SRCS:%.c=%.o)
OBJ_COREWAR = $(COREWAR_SRCS:%.c=%.o)
INCLUDES = -I ./includes
MAIN_ASM = asm_srcs/main.o
LIBFT_H = -I ./libft/includes
PRTF_H = -I ./ft_printf
NAME_ASM = asm
NAME_COREWAR = corewar
CFLAGS =  -Wall -Werror -Wextra
NORM = norminette $(ASM_SRCS) $(COREWAR_SRCS) | grep -e "Error" -e "Warning" -B 1

COLOR_GREEN = $(shell printf "\e[38;5;10m")
COLOR_RED = $(shell printf "\e[31;5;10m")
COLOR_YELLOW = $(shell printf "\e[33;5;10m")
COLOR_DEFAULT = $(shell printf "\e[39m")
PRINT_PLUS = $(shell printf '$(COLOR_GREEN)[ + ]$(COLOR_DEFAULT)')
PRINT_CLEAN = $(shell printf '$(COLOR_RED)[ - ]$(COLOR_DEFAULT)')
PRINT_DONE = $(shell printf '$(COLOR_YELLOW)[ › ]$(COLOR_DEFAULT)')

all: $(NAME_ASM) $(NAME_COREWAR)

%.o: %.c includes/vm.h includes/op.h includes/asm.h
	@gcc $< -c -o $@ $(CFLAGS) $(INCLUDES) $(LIBFT_H) $(PRTF_H)
	@echo "$(PRINT_PLUS) $@"

$(NAME_COREWAR): $(OBJ_COREWAR) libft/libft.a ft_printf/libftprintf.a
	@gcc $(CFLAGS) $(OBJ_COREWAR) -lncurses libft/libft.a -o $@ ft_printf/libftprintf.a -o $@
	@echo "$(PRINT_DONE) Compiling corewar completed"

$(NAME_ASM): $(MAIN_ASM) $(OBJ_ASM) libft/libft.a ft_printf/libftprintf.a
	@gcc $(CFLAGS) $(MAIN_ASM) $(OBJ_ASM) libft/libft.a -o $@ ft_printf/libftprintf.a -o $@
	@echo "$(PRINT_DONE) Compiling asm completed"

libft/libft.a: FORCE
	@make -C libft/

ft_printf/libftprintf.a: FORCE
	@make -C ft_printf/

test_asm:
	@make -C unit_test/

test_corewar:
	cd unit_test && ./exec_test.sh && cd .. && make clean

clean:
	@rm -f $(OBJ_COREWAR) $(OBJ_ASM)
	@make -C ./libft clean
	@make -C ./ft_printf clean
	@make -C ./unit_test clean
	@make -C ./unit_test/support/tester clean
	@echo "$(PRINT_CLEAN) Cleaning objectives completed"

fclean: clean
	@rm -f $(NAME_ASM) $(NAME_COREWAR)
	@make -C ./libft fclean
	@make -C ./ft_printf fclean
	@make -C ./unit_test fclean
	@make -C ./unit_test/support/tester fclean
	@echo "$(PRINT_CLEAN) Cleaning all completed"

re:
	@make fclean
	@make all

norm:
	@echo "===================NORMINETTE==================="
	@$(NORM) || echo "no norminette errors"
	@echo "================================================"

FORCE:

.PHONY: all clean fclean re norm asm test_asm test_corewars

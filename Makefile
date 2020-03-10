# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: igvan-de <igvan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/18 17:58:55 by igvan-de       #+#    #+#                 #
#    Updated: 2020/02/18 13:13:36 by jdunnink      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include vm_srcs/sources

OBJ_COREWAR = $(SRCS:%.c=%.o)
INCLUDES = -I ./includes

NAME = corewar
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

%.o: %.c includes/vm.h
	@gcc $< -c -o $@ $(CFLAGS) $(INCLUDES)
	@echo "$(PRINT_PLUS) $@"

corewar: $(OBJ_COREWAR) libft/libft.a
	@gcc $(CFLAGS) $(OBJ_COREWAR) -lncurses libft/libft.a -o $@
	@echo "$(PRINT_DONE) Compiling corewar completed"

libft/libft.a: FORCE
	@make -C libft/

unit_test:
	@make -C unit_test/

test:
	cd unit_test && ./exec_test.sh

clean:
	@rm -f $(OBJ_COREWAR)
	@make -C ./Libft clean
	@echo "$(PRINT_CLEAN) Cleaning objectives completed"

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean
	@echo "$(PRINT_CLEAN) Cleaning all completed"

re:
	@make fclean
	@make all

norm:
	@echo "===================NORMINETTE==================="
	@$(NORM) || echo "no norminette errors"
	@echo "================================================"

FORCE:

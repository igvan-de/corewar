# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: igvan-de <igvan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/18 17:58:55 by igvan-de       #+#    #+#                 #
#    Updated: 2020/02/17 17:11:59 by igvan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include asm/sources
include asm/error_functions/sources

OBJ_ASM = $(SRCS:%.c=%.o)
OBJ_COREWAR = $(CORESRCS:%.c=%.o)
INCLUDES = -I ./includes

NAME = asm corewar
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

%.o: %.c includes/lemin.h
	@gcc $< -c -o $@ $(CFLAGS) $(INCLUDES)
	@echo "$(PRINT_PLUS) $@"

asm: $(ASM_FILES) libft/libft.a
	@gcc $(CFLAGS) $(OBJ_AMS) libft/libft.a -o $@
	@echo "$(PRINT_DONE) Compiling asm completed"

corewar: $(COREWAR_FILES) libft/libft.a
	@gcc $(CFLAGS) $(OBJ_COREWAR) libft/libft.a -o $@
	@echo "$(PRINT_DONE) Compiling corewar completed"

libft/libft.a: FORCE
	@make -C libft/

unit_test:
	@make -C unit_test/

clean:
	@rm -f $(OBJ_FILES)
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

# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: igvan-de <igvan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/18 17:58:55 by igvan-de       #+#    #+#                 #
#    Updated: 2020/02/13 14:12:23 by igvan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include sources

COLOR_GREEN = $(shell printf "\e[38;5;10m")
COLOR_RED = $(shell printf "\e[31;5;10m")
COLOR_YELLOW = $(shell printf "\e[33;5;10m")
COLOR_DEFAULT = $(shell printf "\e[39m")

NAME = asm corewar
OBJ_ASM = $(ASM:%.c=%.o)
OBJ_COREWAR = $(COREWAR:%.c=%.o)
INCLUDES = -I ./includes
CFLAGS =  -Wall -Werror -Wextra
NORM = norminette $(SRCS) | grep -e "Error" -e "Warning" -B 1
PRINT_PLUS = $(shell printf '$(COLOR_GREEN)[ + ]$(COLOR_DEFAULT)')
PRINT_CLEAN = $(shell printf '$(COLOR_RED)[ - ]$(COLOR_DEFAULT)')
PRINT_DONE = $(shell printf '$(COLOR_YELLOW)[ › ]$(COLOR_DEFAULT)')

all: $(NAME)

%.o: %.c includes/lemin.h
	@gcc $< -c -o $@ $(CFLAGS) $(INCLUDES)
	@echo "$(PRINT_PLUS) $@"

asm: $(ASM_FILES) libft/libft.a
	@gcc $(CFLAGS) $(OBJ_AMS) libft/libft.a -o ams
	@echo "$(PRINT_DONE) Compiling asm completed"

corewar: $(COREWAR_FILES) libft/libft.a
	@gcc $(CFLAGS) $(OBJ_COREWAR) libft/libft.a -o corewar
	@echo "$(PRINT_DONE) Compiling corewar completed"

libft/libft.a: FORCE
	@make -C libft/

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

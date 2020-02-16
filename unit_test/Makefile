# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: igvan-de <igvan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/16 09:11:59 by igvan-de       #+#    #+#                 #
#    Updated: 2020/02/16 10:46:22 by igvan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include sources
include ../sources/coresrcs

OBJ_FILES = $(TESTSRCS=%.c=%.o)
OBJ_FILES += $(SRCS=%.c=%.o)
INCLUDES = -I .././includes

NAME = coretest
CFLAGS = -Wall -Werror
CRITERION := -L $(HOME)/.brew/lib -lcriterion
LIB = .././libft/libft.a
AMS = ../asm
COREWAR = ../corewar

COLOR_GREEN = $(shell printf "\e[38;5;10m")
COLOR_RED = $(shell printf "\e[31;5;10m")
COLOR_DEFAULT = $(shell printf "\e[39m")
PRINT_PLUS = $(shell printf '$(COLOR_GREEN)[ + ]$(COLOR_DEFAULT)')
PRINT_CLEAN = $(shell printf '$(COLOR_RED)[ - ]$(COLOR_DEFAULT)')

all: $(NAME)

%.o: %.c
	@gcc $< -c -o $@ $(CFLAGS) $(INCLUDES)
	@echo "$(PRINT_PLUS) $@"

$(NAME): $(ASM) $(COREWAR) $(OBJ_FILES)
	@gcc -coverage $(CRITERION) $(OBJ_FILES) $(CFLAGS) $(LIB) -o $@

$(ASM): FORCE
	@Meke -C ../

$(COREWAR): FORCE
	@Meke -C ../

clean:
	@rm -f $(OBJ_FILES)
	@echo "$(PRINT_CLEAN) Cleaning objectives completed"

flcean: clean
	@rm -f $(NAME)
	@echo "$(PRINT_CLEAN) Cleaning all completed"

re:
	@make fclean
	@make all

FORCE:

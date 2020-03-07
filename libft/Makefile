# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: igvan-de <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/17 12:10:38 by igvan-de       #+#    #+#                 #
#    Updated: 2020/02/13 14:04:39 by igvan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include sources

COLOR_GREEN = $(shell printf "\e[38;5;10m")
COLOR_DEFAULT = $(shell printf "\e[39m")

NAME = libft.a
OBJ := $(SRCS:%.c=%.o)
INCLUDE = -I .././includes
FLAGS = -Wall -Werror -Wextra $(INCLUDE)
NORM = norminette $(SRCS) $(HEADER) | grep -e "Error" -e "Warning" -B 1
PRINT_PLUS = $(shell printf '$(COLOR_GREEN)[ + ]$(COLOR_DEFAULT)')

all: $(NAME)

%.o: %.c .././includes/libft.h
	@gcc $< -c -o $@ $(FLAGS) $(INCLUDE)
	@echo "$(PRINT_PLUS) $@"

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

author:
	@rm -f author
	@touch author
	@echo | env LOGNAME >>author
	@echo "Authorfile is made"

re: fclean all

print:
	@echo "$(OBJ)"

norm:
	@echo "===============NORMINETTE==============="
	@$(NORM) || echo "no norminette errors"
	@echo "========================================"

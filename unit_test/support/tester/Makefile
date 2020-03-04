# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lravier <marvin@codam.nl>                    +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/18 08:51:33 by lravier        #+#    #+#                 #
#    Updated: 2020/03/02 10:27:51 by jdunnink      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cw_tester

SRC =	main.c					\

OBJ = $(SRC:.c=.o)
SRCDIR = srcs
OBJDIR = objs

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

HEADER = -I includes/ -I libft/includes/
cc = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = -L libft/ -lft

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/ 
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(HEADER) $(LIB)

$(OBJS): $(SRCS)
	/bin/mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $(SRCS) $(HEADER)
	/bin/mv $(OBJ) $(OBJDIR)/

clean:
	/bin/rm -Rf $(OBJDIR)
	/bin/rm -Rf *~ *#
	make -C libft/ clean

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

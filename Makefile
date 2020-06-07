# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: igvan-de <igvan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/18 17:58:55 by igvan-de      #+#    #+#                  #
#    Updated: 2020/05/02 15:58:24 by igor          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include vm_srcs/sources
include dsm_srcs/sources
include asm_srcs/utility/sources
include asm_srcs/error_functions/sources
include asm_srcs/asm_to_byte/sources
include asm_srcs/check_file/sources

OBJ_ASM = $(ASM_SRCS:%.c=%.o)
OBJ_DSM = $(DSM_SRCS:%.c=%.o)
OBJ_CW = $(COREWAR_SRCS:%.c=%.o)
VIS = -lncurses
INCLUDES = -I ./includes
LIBFT_H = -I ./libft/includes
LIBFT_A = libft/libft.a
PRTF_H = -I ./ft_printf
PRTF_A = ft_printf/libftprintf.a
NAME_ASM = asm
NAME_DSM = dsm
NAME_CW = corewar
CFLG =  -Wall -Werror -Wextra

COLOR_GREEN = $(shell printf "\e[38;5;10m")
COLOR_RED = $(shell printf "\e[31;5;10m")
COLOR_YELLOW = $(shell printf "\e[33;5;10m")
COLOR_DEFAULT = $(shell printf "\e[39m")
PRINT_PLUS = $(shell printf '$(COLOR_GREEN)[ + ]$(COLOR_DEFAULT)')
PRINT_CLEAN = $(shell printf '$(COLOR_RED)[ - ]$(COLOR_DEFAULT)')
PRINT_DONE = $(shell printf '$(COLOR_YELLOW)[ › ]$(COLOR_DEFAULT)')

all: $(NAME_ASM) $(NAME_CW) $(NAME_DSM)

%.o: %.c includes/vm.h includes/op.h includes/asm.h includes/dsm.h
	@gcc $< -c -o $@ $(CFLG) $(INCLUDES) $(LIBFT_H) $(PRTF_H)
	@echo "$(PRINT_PLUS) $@"

$(NAME_CW): $(OBJ_CW) $(LIBFT_A) $(PRTF_A)
	@gcc $(CFLG) $(OBJ_CW) $(VIS) $(LIBFT_A) -o $@ $(PRTF_A) -o $@
	@echo "$(PRINT_DONE) Compiling corewar completed"

$(NAME_ASM): $(OBJ_ASM) $(LIBFT_A) $(PRTF_A)
	@gcc $(CFLG) $(OBJ_ASM) $(LIBFT_A) -o $@ $(PRTF_A) -o $@
	@echo "$(PRINT_DONE) Compiling asm completed"

$(NAME_DSM): $(OBJ_DSM) $(LIBFT_A) $(PRTF_A)
	@gcc $(CFLG) $(OBJ_DSM) $(LIBFT_A) -o $@ $(PRTF_A) -o $@
	@echo "$(PRINT_DONE) Compiling dsm completed"

libft/libft.a:
	@make -C libft/

ft_printf/libftprintf.a:
	@make -C ft_printf/

clean:
	@rm -f $(OBJ_CW) $(OBJ_ASM) $(OBJ_DSM)
	@make -C ./libft clean
	@make -C ./ft_printf clean
	@echo "$(PRINT_CLEAN) Cleaning objectives completed"

fclean: clean
	@rm -f $(NAME_ASM) $(NAME_CW) $(NAME_DSM)
	@make -C ./libft fclean
	@make -C ./ft_printf fclean
	@echo "$(PRINT_CLEAN) Cleaning all completed"

re:
	@make fclean
	@make all

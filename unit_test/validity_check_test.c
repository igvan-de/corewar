/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validity_check_test.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 12:22:46 by igvan-de       #+#    #+#                */
/*   Updated: 2020/03/05 12:34:06 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include "asm.h"

Test()
{
	/*read input function*/
	/*
	1. needs to read from fd
	2. needs to keep reading while get_next_line returns bigger then 0
	3. needs to go to validation check
	*/
}

Test()
{
	/*validatin checker */
	/*
	2. need to receive line as parameter
	3. line can't be NULL
	4. needs to check if file has .name
	5. .name string cant be bigger then PROG_NAME_LENGHT
	6. needs to check if file has .comment
	7. .comment cant be bigger then COMMENT_LENGTH
	*/
}

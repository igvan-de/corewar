/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cor_test.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 12:22:46 by igvan-de       #+#    #+#                */
<<<<<<< HEAD
/*   Updated: 2020/03/11 17:32:41 by igvan-de      ########   odam.nl         */
=======
/*   Updated: 2020/03/11 13:51:57 by igvan-de      ########   odam.nl         */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "asm.h"

// static void redirect_std_out(void)
// {
// 	cr_redirect_stdout();
// }

// static void redirect_std_err(void)
// {
// 	cr_redirect_stderr();
// }

// static void redirect_std_err_out(void)
// {
// 	cr_redirect_stdout();
// 	cr_redirect_stderr();
// }

<<<<<<< HEAD
/*
** @brief Construct a new Test object
** tests if the directory is wrong or non existing
*/

Test(unit_create_cor_test, only_space_test)
{
	t_func_list *list = (t_func_list*)ft_memalloc(sizeof(t_func_list));
	char *argv;

	argv = " ";
	create_cor_file(argv, list);
	cr_assert_neq(0, access("barriere.cor", F_OK));
}

/*
** @brief Construct a new Test object
** tests if name of champion has a . in it
*/

Test(unit_create_cor_test, wrong_input_test)
=======
Test(unit_create_cor_test, simple_input_test)
>>>>>>> master
{
	t_func_list *list = (t_func_list*)ft_memalloc(sizeof(t_func_list));
	char *argv;

<<<<<<< HEAD
	argv = "../vm_champs/champs/barri.ere";
=======
	argv = "../test_champs/champs/barriere.s";
>>>>>>> master
	create_cor_file(argv, list);
	cr_assert_eq(0, access("barriere.cor", F_OK));
}

<<<<<<< HEAD
/*
** @brief Construct a new Test object
** tests when the correct input is given and of result is correct
*/

Test(unit_create_cor_test, simple_input_test)
{
	t_func_list *list = (t_func_list*)ft_memalloc(sizeof(t_func_list));
	char *argv;

	argv = "../vm_champs/champs/barriere.s";
	create_cor_file(argv, list);
	cr_assert_eq(0, access("barriere.cor", F_OK));
}
=======

>>>>>>> master



// Test()
// {
// 	/*read input function*/
// 	/*
// 	1. needs to read from fd
// 	2. needs to keep reading while get_next_line returns bigger then 0
// 	3. needs to go to validation check
// 	*/
// }

// Test()
// {
// 	/*validation checker */
// 	/*
// 	2. need to receive line as parameter
// 	3. line can't be NULL
// 	4. needs to check if file has .name
// 	5. .name string cant be bigger then PROG_NAME_LENGHT
// 	6. needs to check if file has .comment
// 	7. .comment cant be bigger then COMMENT_LENGTH
// 	*/
// }

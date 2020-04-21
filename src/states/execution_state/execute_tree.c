/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   execute_tree.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/07 21:21:47 by adandres               /    /  /         */
/*   Updated: 2020/04/21 17:17:55 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

t_return	*init_ret(void)
{
	t_return	*ret;

	ret = (t_return*)malloc(sizeof(t_return));
	ret->n_proc = 0;
	ret->n_file = 0;
	ret->n_copy = 0;
	ret->status = 0;
	ret->fd_out = dup(STDOUT_FILENO);
	return (ret);
}

void    execute_tree(t_state **machine)
{
	t_return *ret;
	if ((*machine)->is_debug)
		printf("count : %d\n", (*machine)->is_debug);
	if ((*machine)->is_debug)
		printf("\n--------    Start_execution    --------\n\n\n");
	ret = init_ret();
	exec_loop((*machine)->tree, machine, &ret, SEMI);
	//if ((*machine)->count >= 136)
	//	while (1);
	if ((*machine)->is_debug)
		printf("after_loop\n");
	(*machine)->status = ret->status;
	free(ret);
	reset(*machine);
	(*machine)->state = READ;
	if ((*machine)->status && (*machine)->is_debug)
		printf("\n--------    FAILURE    --------\n");
	else if ((*machine)->is_debug)
		printf("\n--------    SUCCESS    --------\n\n\n");
}

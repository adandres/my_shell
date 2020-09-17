/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   execute_tree.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/07 21:21:47 by adandres               /    /  /         */
/*   Updated: 2020/06/27 14:57:20 by adandres                                 */
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

void	history(char ***p_history, char *cmd)
{
	char	**hist;
	char	*tmp;
	char	*prev;
	int	i;

	i = 0;
	prev = NULL;
	hist = *p_history;
	if (hist[i] != NULL)
		prev = hist[i];
	hist[i] = my_strdup(cmd);
	i++;
	while (i < 256 && prev != NULL)
	{
		if (i == 255 && hist[i])
			free(hist[i]);
		tmp = hist[i];
		hist[i] = prev;
		prev = tmp;
		i++;
	}
	*p_history = hist;
}

void    execute_tree(t_state **machine)
{
	t_return *ret;
	if ((*machine)->is_debug)
		printf("\n--------    Start_execution    --------\n\n\n");
	ret = init_ret();
	exec_loop((*machine)->tree, machine, &ret, SEMI);
	(*machine)->status = (ret->status == 0) ? 0 : 1;
	if ((*machine)->relaunch == 0)
	history(&(*machine)->history, (*machine)->cmd);
	free(ret);
	reset(*machine);
	if ((*machine)->state != END)
		(*machine)->state = READ;
	if ((*machine)->status && (*machine)->is_debug)
		printf("\n--------    FAILURE    --------\n");
	else if ((*machine)->is_debug)
		printf("\n--------    SUCCESS    --------\n\n\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   relaunch.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:25:54 by adandres               /    /  /         */
/*   Updated: 2020/07/01 16:21:54 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static t_state *setup_relaunch(char **argv, char **cpy)
{
	t_state *machine;

	machine = (t_state*)malloc(sizeof(t_state));
	machine->env = my_tabdup(cpy);
	machine->file_fd = -1;
	machine->status = 0;
	machine->set = NULL;
	machine->history = NULL;
	machine->relaunch = 1;
	machine->is_debug = 0;
	return (machine);
}

int			relaunch(char **argv, char ***cpy)
{
	t_state		*machine;

	if (!(machine = setup_relaunch(argv, *cpy)))
		printf("error\n");
	machine->cmd = my_strjoin_tab(argv, " ");
	parse_input(&machine);
	build_state(&machine);
	execute_tree(&machine);
	if (machine->env)
	{
		free_tab(*cpy);
		*cpy = machine->env;
	}
	free(machine);
	return (0);
}

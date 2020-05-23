/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   relaunch.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:25:54 by adandres               /    /  /         */
/*   Updated: 2020/04/22 17:59:51 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int			no_read_shell(char **argv, char **cpy)
{
	t_state		*machine;

	if (!(machine = start_machine(0, NULL, cpy)))
		return (1);
	machine->cmd = my_strjoin_tab(argv, " ");
	parse_input(&machine);
	build_state(&machine);
	execute_tree(&machine);
	if (machine->my_env)
		free_tab(machine->my_env);
	free(machine);
	return (0);
}

int			relaunch(char **argv, char **cpy)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		exit(EXIT_SUCCESS);
	if (pid == 0)
	{
		no_read_shell(argv, cpy);
		exit(EXIT_SUCCESS);
	}
	else
		wait(&pid);
	return (pid);
}

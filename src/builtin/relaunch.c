/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   relaunch.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:25:54 by adandres               /    /  /         */
/*   Updated: 2020/05/30 15:00:09 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int			no_read_shell(char **argv, char **cpy)
{
	t_state		*machine;

	if (!(machine = start_machine(0, argv, cpy)))
		printf("error\n");
	machine->my_env = my_tabdup(cpy);
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

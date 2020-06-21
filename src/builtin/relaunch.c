/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   relaunch.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:25:54 by adandres               /    /  /         */
/*   Updated: 2020/06/21 13:22:14 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int			relaunch(char **argv, char **cpy)
{
	t_state		*machine;

	if (!(machine = start_machine(1, argv, cpy)))
		printf("error\n");
	machine->cmd = my_strjoin_tab(argv, " ");
	parse_input(&machine);
	build_state(&machine);
	execute_tree(&machine);
	if (machine->env)
		free_tab(machine->env);
	free(machine);
	return (0);
}

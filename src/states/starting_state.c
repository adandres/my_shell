/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   starting_state.c                                /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 17:13:38 by adandres               /    /  /         */
/*   Updated: 2020/04/16 19:30:08 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void		check_if_file(t_state **machine, int argc, char **argv)
{
	if (argv[1] && my_strcmp(argv[1], "-debug") == 0 && argc == 2 && isatty(0))
		(*machine)->is_debug = 1;
	else if (argv[1] || isatty(0))
	{
		if (argv[1] == NULL)
			(*machine)->file_fd = 0;
		if (argv[1] && ((*machine)->file_fd = open(argv[1], O_RDONLY)) < 0)
		{
			printf("42sh: %s: No such file or directory\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}
}



t_state	*start_machine(int argc, char **argv, char **env)
{
	t_state		*machine;

	if (!(machine = (t_state*)malloc(sizeof(t_state))))
		return (NULL);
	machine->file_fd = -1;
	machine->status = 0;
	machine->easter_egg = 0;
	machine->is_debug = 0;
	machine->tree = NULL;
	machine->cmd = NULL;
	machine->my_env = NULL;
	machine->token_list = NULL;
	if (env && env[0])
		machine->my_env = my_tabdup(env);
	//machine->my_env = set_env(env);
	if (argc > 1)
		check_if_file(&machine, argc, argv);
	machine->state = READ;
	return (machine);
}

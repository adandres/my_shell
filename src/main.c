/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   main.c                                          /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 17:12:02 by adandres               /    /  /         */
/*   Updated: 2020/04/13 01:42:32 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	main(int ac, char **av, char **env)
{
	t_state			*machine;
	static void		(*state_func[5])(t_state **) = { \
				&read_input, &parse_input, \
				&expand_input, &build_state, &execute_tree};

	if (!(machine = start_machine(ac, av, env)))
		return (1);
	if (machine->file_fd != -1)
		state_func[READ] = &read_file;
	while (machine->state != END)
	{
		(state_func[machine->state])(&machine);
	}
	//free_all(machine);
	return (0);
}

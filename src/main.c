/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   main.c                                          /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 17:12:02 by adandres               /    /  /         */
/*   Updated: 2020/05/24 19:59:48 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	main(int ac, char **av, char **env)
{
	int			fd;
	t_state			*machine;
	static void		(*state_func[4])(t_state **) = { \
				&read_input, &parse_input, \
				&build_state, &execute_tree};

	if (!(machine = start_machine(ac, av, env)))
		return (1);
	if (machine->file_fd != -1)
		state_func[READ] = &read_file;
	while (machine->state != END)
	{
		(state_func[machine->state])(&machine);
	}	
	fd = open(".my_shell_history", O_WRONLY | O_TRUNC);
	machine->history = my_tab_reverse(machine->history);
	print_tab_fd(machine->history, fd);
	close(fd);
	free_all(machine);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   exec_builtin.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 13:26:48 by adandres               /    /  /         */
/*   Updated: 2020/06/22 18:54:18 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void		free_leaf(t_cmd *cmd);

/*int		exec_builtin(t_state **machine, t_cmd *cmd)
{
	static int	(*builtin_func[7])(char **argv, t_state **machine) = \
	{&exit_prog, &ft_echo, &change_directory, \
		&my_env, &my_unsetenv, &my_set, &my_export};

	
	(*machine)->status = (builtin_func[cmd->builtin])(cmd->argv, machine);
	return (0);
}*/

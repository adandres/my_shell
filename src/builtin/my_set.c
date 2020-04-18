/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_set.c                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/16 16:45:34 by adandres               /    /  /         */
/*   Updated: 2020/04/17 22:42:18 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int relaunch(char **argv, char **cpy);

int				my_set(char **argv, t_state **machine)
{
	char	**env;
	int	i;

	env = NULL;
	i = 1;
	if (env)
		env = my_tabdup((*machine)->my_env);
	while (argv[i])
	{
		if (my_strichr(argv[i], '='))
			env = add_new_env(argv[i], env);
		i++;
	}
	if (i == 0 && env)
		print_tab(env);
	if ((*machine)->my_env != NULL)
		free_tab((*machine)->my_env);
	if (env)
		(*machine)->my_env = env;
	return (0);
}

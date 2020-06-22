/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_set.c                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/16 16:45:34 by adandres               /    /  /         */
/*   Updated: 2020/06/22 13:25:50 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int relaunch(char **argv, char **cpy);

int				my_set(char **argv, t_state **machine)
{
	char	**set;
	int	i;

	set = NULL;
	i = 0;
	if ((*machine)->set)
		set = my_tabdup((*machine)->set);
	while (argv[i])
	{
		if (my_strichr(argv[i], '=') >= 0)
			set = add_new_env(argv[i], set);
		i++;
	}
	if (set)
		print_tab(set);
	if ((*machine)->set != NULL)
		free_tab((*machine)->set);
	if (set)
		(*machine)->set = set;
	return (0);
}

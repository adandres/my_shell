/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_set.c                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/16 16:45:34 by adandres               /    /  /         */
/*   Updated: 2020/07/06 12:51:42 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int relaunch(char **argv, char ***cpy);

int				is_cmd(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] && my_strichr(argv[i], '=') >= 0)
		i++;
	if (argv[i] == NULL)
		return (0);
	return (1);
}

int				my_spe_set(char **argv, t_state **machine)
{
	int	i;
	char	*command;

	i = 0;
	if (is_cmd(argv) == 0)
		return (my_set(argv, machine));
	while (argv[i] && my_strichr(argv[i], '=') >= 0)
	{
		(*machine)->env = add_new_env(argv[i], (*machine)->env);
		i++;
	}
	if (is_builtin(argv[i], CMD) < 0)
	{
		command = get_cmd_path(argv[i], (*machine)->env);
		if (command)
		{
			free(argv[i]);
			argv[i] = command;
		}
	}
	relaunch(argv + i, &(*machine)->env);
	i--;
	while (i >= 0)
	{
		(*machine)->env = my_unset(argv[i], (*machine)->env);
		i--;
	}
	return (0);
}

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
	if (i == 1 && my_strcmp("set", argv[0]) == 0)
		print_tab(set);
	if ((*machine)->set != NULL)
		free_tab((*machine)->set);
	if (set)
		(*machine)->set = set;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_unsetenv.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/08 19:18:15 by adandres               /    /  /         */
/*   Updated: 2020/07/03 07:52:49 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char		**my_unset(char *argv, char **env)
{
	char		**new_env;
	int		index;
	int		i;

	i = 0;
	if ((index = env_index(env, argv)) == -1)
		return (env);
	while (env[i])
		i++;
	if (!(new_env = (char**)malloc(sizeof(char*) * i)))
		exit(EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		if (i < index)
			new_env[i] = env[i];
		if (i > index)
			new_env[i - 1] = env[i];
		if (i == index)
			free(env[i]);
		i++;
	}
	new_env[i - 1] = NULL;
	free(env);
	return (new_env);
}


int		my_unsetenv(char **argv, t_state **machine)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (my_strchr(argv[i], '='))
		{
			printf("Nope\n");
			return (1);
		}
		if (env_index((*machine)->env, argv[i]) >= 0)
			(*machine)->env = my_unset(argv[i], (*machine)->env);
		if (env_index((*machine)->set, argv[i]) >= 0)
			(*machine)->set = my_unset(argv[i], (*machine)->set);
		i++;
	}
	return (0);
}

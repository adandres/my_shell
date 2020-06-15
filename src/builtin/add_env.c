/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   add_env.c                                       /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/08 18:27:48 by adandres               /    /  /         */
/*   Updated: 2020/06/04 14:52:00 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char	**update_env(char *src, char **env, int index)
{
	free(env[index]);
	env[index] = my_strdup(src);
	return (env);
}

char		**add_or_update_env(char *name, char *var, char **env)
{
	char	*full;

	full = my_strjoin(name, "=");
	full = my_strjoin_free(full, var);
	env = add_new_env(full, env);
	free(full);
	return (env);
}

char		**add_new_env(char *new, char **env)
{
	char	**new_env;
	char	*name;
	int	index;

	name = get_name(new);
	index = env_index(env, name);
	if (index < 0)
		new_env = my_tab_add_str_end(new, env);
	else
		new_env = update_env(new, env, index);
	free(name);
	return (new_env);
}

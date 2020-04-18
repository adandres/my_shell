/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   add_env.c                                       /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/08 18:27:48 by adandres               /    /  /         */
/*   Updated: 2020/04/18 19:07:16 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char	**reeeee(char *src, char **env, int index)
{
	free(env[index]);
	env[index] = my_strdup(src);
	return (env);
}

char	**my_stradd_tab(char *src, char **tab)
{
	int		len;
	char		**new_tab;
	
	len = my_tablen(tab);
	if (!(new_tab = (char**)realloc(tab, sizeof(char*) * (len + 2))))
		return (NULL);
	new_tab[len] = my_strdup(src);
	new_tab[len + 1] = NULL;
	return (new_tab);
}

char		**add_new_env(char *new, char **env)
{
	char	**new_env;
	char	*name;
	int	index;

	name = get_name(new);
	index = env_index(env, name);
	if (index < 0)
		new_env = my_stradd_tab(new, env);
	else
		new_env = reeeee(new, env, index);
	free(name);
	return (new_env);
}

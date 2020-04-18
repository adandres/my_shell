/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cmd_path.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 20:29:16 by adandres               /    /  /         */
/*   Updated: 2020/04/17 19:19:18 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char		*path_explore(char *path, char *input)
{
	char		*cmd_path;


	cmd_path = my_strjoin(path, "/");
	cmd_path = my_strjoin_free(cmd_path, input);
	if (access(cmd_path, F_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

char		*path_search(char *path_list, char *input)
{
	char		**path;
	char		*cmd_path;
	int		i;

	i = 0;
	path = my_strsplit(path_list, ':');
	while (path[i])
	{
		if ((cmd_path = path_explore(path[i], input)) != NULL)
			break;
		i++;
	}
	free_tab(path);
	return (cmd_path);
}

static char	*get_path(char *input, char **env)
{
	char	*path_list;
	char	*path;

	if (access(input, X_OK) == 0)
		return (input);
	if (env == NULL)
		return (NULL);
	path_list = get_env_var(env, "PATH");
	if (path_list)
		path = path_search(path_list, input);
	else
		printf("error: No PATH set\n");
	if (path_list)
		free(path_list);
	else
		path = NULL;
	return (path);
}

char	*get_cmd_path(char *command, char **env)
{
	char		*path;

	path = get_path(command, env);
	return (path);
}

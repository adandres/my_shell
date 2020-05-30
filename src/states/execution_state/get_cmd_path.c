/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cmd_path.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 20:29:16 by adandres               /    /  /         */
/*   Updated: 2020/05/29 17:17:17 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	is_dir(char *path)
{
	DIR		*is_dir;
	char		*test_path;
	int		len;

	len = my_strlen(path);
	test_path = my_strjoin(path ,"/");
	is_dir = opendir(test_path);
	if (is_dir != NULL)
	{
		free(test_path);
		closedir(is_dir);
		return (1);
	}
	free(test_path);
	if (len == 1 && (path[0] == '.' || path[0] == '/' || path[0] == '\\' || path[0] == '~'))
		return (1);
	return (0);
}

static int	is_exec_file(char *path)
{

	if (is_dir(path))
		return (0);
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

char		*path_explore(char *path, char *input)
{
	char		*cmd_path;

	cmd_path = my_strjoin(path, "/");
	cmd_path = my_strjoin_free(cmd_path, input);
	if (is_exec_file(cmd_path))
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

	path = NULL;
	if (is_dir(input) == 1)
		return (NULL);
	if (is_exec_file(input))
		return (my_strdup(input));
	if (env == NULL)
		return (NULL);
	path_list = get_env_var(env, "PATH");
	if (path_list)
		path = path_search(path_list, input);
	else
		my_printf("error: No PATH set\n");
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

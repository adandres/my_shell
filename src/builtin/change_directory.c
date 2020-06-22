/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   change_directory.c                              /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/08 01:18:49 by adandres               /    /  /         */
/*   Updated: 2020/06/22 19:06:51 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static char		*filename_dir(char *filename, char **env)
{
	char	*str;
	int		i;

	if (my_strcmp(filename, "-") == 0)
	{
		if ((i = env_index(env, "OLDPWD")) == -1)
		{
			my_putendl("Error: cd:  OLDPWD not set");
			return (NULL);
		}
		str = get_var(env[i]);
		my_printf("%s\n", str);
	}
	else if (access(filename, F_OK) == 0)
		str = my_strdup(filename);
	else
	{
		printf("zut_i\n");
		return (NULL);
	}
	return (str);
}

static char		*new_directory(char *filename, char **env)
{
	int			i;
	char		*str;

	i = 0;
	if (filename && env)
		str = filename_dir(filename, env);
	else
	{
		if (env)
			i = env_index(env, "HOME");
		if (i == -1 || !env)
		{
			my_putstr("cd: HOME not set\n");
			return (NULL);
		}
		str = my_strdup(env[i] + 5);
	}
	return (str);
}

int		change_directory(char **argv, t_state **machine)
{
	char		*path;
	char		**env;
	char		*str;

	env = (*machine)->env;
	if ((str = new_directory(argv[1], env)) == NULL)
		printf("Ah!\n");;
	path = my_strnew(PATH_MAX);
	path = getcwd(path, PATH_MAX);
	env = add_or_update_env("OLDPWD", path, env);
	if (chdir(str) < 0)
	{
		printf("zut_e\n");
		return (1);
	}
	free(path);
	path = my_strnew(PATH_MAX);
	path = getcwd(path, PATH_MAX);
	env = add_or_update_env("PWD", path, env);
	(*machine)->env = env;
	free(str);
	free(path);
	return (0);
}

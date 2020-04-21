/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_env_var.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 20:55:54 by adandres               /    /  /         */
/*   Updated: 2020/04/19 13:58:56 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char		*get_name(char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	ptr = my_strndup(str, i);
	return (ptr);
}

char		*get_var(char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] && str[i + 1])
		i++;
	if (str[i] == '\0')
		return (NULL);
	ptr = my_strdup(str + i);
	return (ptr);
}

char	*get_env_var(char **env, char *var)
{
	int	i;
	char	*var_name;
	char	*res;
	
	i = 0;
	while (env[i])
	{
		var_name = get_name(env[i]);
		if (my_strcmp(var, var_name) == 0)
		{
			free(var_name);
			res = my_strdup(env[i]);
			return (res);
		}
		free(var_name);
		i++;
	}
	return (NULL);
}

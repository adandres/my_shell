/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   extend.c                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:13:50 by adandres               /    /  /         */
/*   Updated: 2020/04/21 19:08:59 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static char	*get_var_env(char **env, char *name)
{
	char	*env_var;
	char	*var;

	if (!(env_var = get_env_var(env, name)))
		return (NULL);
	var = get_var(env_var);
	free(env_var);
	return (var);
}

static char	*get_tail(char *input)
{
	char	*tail;
	int	j;

	j = 0;
	tail = NULL;
	while (input[j] && (my_isalpha(input[j]) || input[j] == '_'))
		j++;
	if (j != 0 && input[j])
		tail = my_strdup(input + j);
	return (tail);
}

static char	*get_truc(char *input)
{
	char	*tail;
	int	j;

	j = 0;
	tail = NULL;
	while (my_isalpha(input[j]) || input[j] == '_')
		j++;
	if (j != 0)
		tail = my_strndup(input, j);
	return (tail);
}

static char		*parameter_expand(char *input, char **env)
{
	char			*var;
	char			*result;
	char			*tail;

	tail = get_tail(input + 1);
	if (!(var = get_truc(input + 1)))
		return (tail);
	result = get_var_env(env, var);
	free(var);
	if (result == NULL)
		return (tail);
	if (tail)
		result = my_strjoin_free(result, tail);
	free(tail);
	return (result);
}

static char	*replace_by_home(char *input, char **env)
{
	int		i;
	char		*path;
	char		*tail;

	i = 0;
	tail = NULL;
	while (input[i] != '~')
		i++;
	if (input[i + 1])
	{
		if (input[i + 1] != '/')
			return (input);
		tail = my_strdup(input + i + 1);
	}
	path = get_var_env(env, "HOME");
	if (tail != NULL)
		path = my_strjoin_free(path, tail);
	free(input);
	if (tail)
		free(tail);
	return (path);
}

static char	*get_param(char *input, int i, char **env)
{
	char	*head;
	char	*expanded;

	head = NULL;
	if (i > 0)
		head = my_strndup(input, i);
	expanded = parameter_expand(input + i, env);
	if (expanded == NULL && head == NULL)
		return (input);
	free(input);
	if (expanded == NULL)
		return (head);
	if (head)
		head = my_strjoin_free(head, expanded);
	else
		head = my_strdup(expanded);
	free(expanded);
	return (head);
}

char		*extand(char *input, char **env)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
		if (input[i] == '~' && i == 0)
			input = replace_by_home(input, env);
	while (input && input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && \
			(quotes == 0 || quotes == input[i]))
		{
			quotes = ((quotes == 0) ? input[i] : 0);
			input = my_strcdel(input, i);
			i--;
		}
		if (input[i] == '$' && input[i + 1] && quotes != '\'')
		{
			input = get_param(input, i, env);
			if ((int)my_strlen(input) <= i)
				return (input);
		}
		i++;
	}
	return (input);
}

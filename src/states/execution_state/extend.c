/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   extend.c                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:13:50 by adandres               /    /  /         */
/*   Updated: 2020/06/21 13:21:39 by adandres                                 */
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
	char	*var;
	char	*result;

	if (!(var = get_truc(input + 1)))
		return (NULL);
	result = get_var_env(env, var);
	free(var);
	return (result);
}

int	replace_by_home(char **input, char **env)
{
	char		*path;
	char		*tail;
	int		len;

	len = 0;
	tail = NULL;
	if ((*input)[1])
	{
		if ((*input)[1] != '/')
			return (0);
		tail = my_strdup(*input + 1);
	}
	path = get_var_env(env, "HOME");
	if (path)
		len = my_strlen(path);
	if (tail && path)
		path = my_strjoin_free(path, tail);
	if (tail && path == NULL)
		path = my_strdup(tail);
	if (tail)
		free(tail);
	free(*input);
	*input = path;
	return (len);
}

int	get_param(char *input, char **extended, char **env)
{
	char	*tail;
	int	len;

	len = 0;
	tail = get_tail(input + 1);
	*extended = parameter_expand(input, env);
	if (*extended)
		len = my_strlen(*extended);
	if (tail)
	{
		if (*extended)
			*extended = my_strjoin_free(*extended, tail);
		else
			*extended = my_strdup(tail);
		free(tail);
	}
	return (len);
}

static	int	check_special_env(char *input, char **dest, t_state *machine)
{
	if (my_strcmp("$$", input) == 0)
		*dest = my_itoa(machine->pid);
	else if (my_strcmp("$?", input) == 0)
		*dest = my_itoa(machine->status);
	else if (my_strcmp("$!", input) == 0)
		printf("3\n");
	else
		return (0);
	return (1);
}

static int	extent(char **input, int i, t_state *machine)
{
	char	*extended;
	char	*head;
	int	len;

	head = NULL;
	if (i != 0)
		head = my_strndup(*input, i);
	if (check_special_env(*input + i, &extended, machine) == 0)
		len = get_param(*input + i, &extended, machine->env);
	free(*input);
	*input = head;
	if (head && extended)
		*input = my_strjoin_free(head, extended);
	else if (extended)
		*input = my_strdup(extended);
	else
		return (-1);
	if (extended)
		free(extended);
	return (len);
}

char		*extand(char *to_ext, t_state *machine)
{
	int	i;
	int	quotes;
	char	*input;

	i = 0;
	quotes = 0;
	input = my_strdup(to_ext);
	if (input[0] == '~')
		i = replace_by_home(&input, machine->env);
	while (input && input[i])
	{
		quotes = check_quotes(input[i], quotes);
		if (input[i] == '$' && input[i + 1] && quotes != '\'')
		{
			if ((i += extent(&input, i, machine)) == -1)
				return (input);
		}
		else
			i++;
	}
	return (input);
}

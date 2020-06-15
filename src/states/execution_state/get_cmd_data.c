/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cmd_data.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:16:43 by adandres               /    /  /         */
/*   Updated: 2020/06/04 16:17:35 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char	**add_argv(char **argv, char *str, int end, int n)
{
	int	i;
	char	*to_add;
	int	quotes;

	quotes = 0;
	i = end;
	while (i > 0 && (not_a_del(str[i]) || quotes != 0))
	{
		quotes = check_quotes(str[i], quotes);
		i--;
	}
	if (!not_a_del(str[i]))
		i++;
	to_add = my_strndup(str + i, end - i + 1);
	argv = my_tab_add_str(to_add, argv, n);
	free(to_add);
	return (argv);
}

char	**add_extended(char **argv, char *str, int *n)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		quotes = check_quotes(str[i], quotes);	
		if (quotes == 0 && not_a_del(str[i]) && not_a_del(str[i + 1]) == 0)
			argv = add_argv(argv, str, i, (*n)++);
		i++;
	}
	return (argv);
}

char	**remove_quotes(char **argv)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	quotes = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] == '\'' || argv[i][j] == '\"') && \
					(quotes == 0 || quotes == argv[i][j]))
			{
				quotes = ((quotes == 0) ? argv[i][j] : 0);
				argv[i] = my_strcdel(argv[i], j);
				j--;
			}
			j++;
		}
		i++;
	}
	return (argv);
}

void	get_cmd_data(t_ast **root, t_state *machine)
{
	t_cmd	*cmd;
	char	**argv;
	char	*extended;
	char	*command;
	int	i;

	i = 0;
	cmd = (*root)->data;
	argv = cmd->argv;
	while (argv[i] != NULL)
	{
		extended = extand(argv[i], machine);
		argv = my_tab_del_str(argv, i);
		if (extended)
		{
			argv = add_extended(argv, extended, &i);
			free(extended);
		}
	}
	argv = remove_quotes(argv);
	command = argv[0];
	if ((*root)->type == CMD && command)
	{
		if (!(cmd->path = get_cmd_path(command, machine->my_env)))
			(*root)->type = NUL;
	}
	machine->my_env = add_or_update_env("_", argv[i - 1], machine->my_env);
	cmd->argv = argv;
	(*root)->data = cmd;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cmd_data.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:16:43 by adandres               /    /  /         */
/*   Updated: 2020/04/22 00:38:04 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char	**merge_tabs(char **tab, int i, char **to_add)
{
	int	tab_len;
	int	len;
	char	**added;
	int	j;

	j = 0;
	tab_len = my_tablen(tab);
	len = my_tablen(to_add) + tab_len;
	free(tab[i]);
	added = (char**)realloc(tab, sizeof(char*) * len);
	while (to_add[j])
	{
		added[i] = my_strdup(to_add[j]);
		i++;
		j++;
	}
	added[i] = NULL;
	return (added);
}

int	is_quoted(char *str)
{
	int	i;
	int	quotes;
	int	quoted;

	i = 0;
	quotes = 0;
	quoted = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && \
				(quotes == 0 || quotes == str[i]))
		{
			quotes = ((quotes == 0) ? str[i] : 0);
			quoted = 1;
		}
		i++;
	}
	return (quoted);
}

void	get_cmd_data(t_ast **root, char **env)
{
	t_cmd	*cmd;
	char	**argv;
	char	**more_argv;
	char	*extended;
	char	*command;
	int	quoted;
	int	i;

	i = 0;
	cmd = (*root)->data;
	argv = my_tabdup(cmd->argv);
	command = extand(argv[0], env);
	while (argv[i] != NULL)
	{
		quoted = is_quoted(argv[i]);
		extended = extand(argv[i], env);
		if (extended && my_strichr(extended, ' ') >= 0 && quoted == 0)
		{
			more_argv = my_strsplit(extended, ' ');
			argv = merge_tabs(argv, i, more_argv);
			if (i == 0)
			{
				free(command);
				command = my_strdup(more_argv[0]);
			}
			free_tab(more_argv);
			free(extended);
		}
		else if (extended)
		{
			free(argv[i]);
			argv[i] = extended;
		}
		else
			argv[i][0] = '\0';
		i++;
	}
	free_tab(cmd->argv);
	if ((*root)->type == CMD && command)
	{
		if (!(cmd->path = get_cmd_path(command, env)))
			(*root)->type = NUL;
	}
	if (command)
		free(command);
	cmd->argv = argv;
	(*root)->data = cmd;
}

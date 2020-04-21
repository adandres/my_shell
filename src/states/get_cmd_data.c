/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cmd_data.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:16:43 by adandres               /    /  /         */
/*   Updated: 2020/04/21 18:57:20 by adandres                                 */
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
	int	quoted;
	int	i;

	i = 0;
	cmd = (*root)->data;
	argv = my_tabdup(cmd->argv);
	while (argv[i] != NULL)
	{
		quoted = is_quoted(argv[i]);
		argv[i] = extand(argv[i], env);
		if (argv[i] && my_strichr(argv[i], ' ') >= 0 && quoted == 0)
		{
			more_argv = my_strsplit(argv[i], ' ');
			argv = merge_tabs(argv, i, more_argv);
			free_tab(more_argv);
		}
		i++;
	}
	free_tab(cmd->argv);
	if ((*root)->type == CMD && argv[0])
	{
		if (!(cmd->path = get_cmd_path(argv[0], env)))
			(*root)->type = NUL;
	}
	cmd->argv = argv;
	(*root)->data = cmd;
}

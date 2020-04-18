/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cmd_data.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:16:43 by adandres               /    /  /         */
/*   Updated: 2020/04/18 19:18:48 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

/*static void	swap(void **a, void **b)
{
	void *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	prendre_tab(char **tab)
{
	int	i;

	i = 1;
	while (tab[i + 1])
	{
		if (my_strcmp(tab[i], tab[i + 1]) < 0)
		{
			swap((void**)&tab[i], (void**)&tab[i + 1]);
			i = 1;
		}
		else
			i++;
	}
}*/

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

t_cmd	*get_cmd_data(t_cmd *arg, char **env)
{
	t_cmd	*cmd;
	char	**argv;
	char	**more_argv;
	int	quoted;
	int	i;

	i = 0;
	arg->path = NULL;
	argv = my_tabdup(arg->argv);
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
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	cmd->path = get_cmd_path(argv[0], env);
	cmd->argv = my_tabdup(argv);
	cmd->builtin = arg->builtin;
	free_tab(argv);
	return (cmd);
}

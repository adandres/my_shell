/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   handle_multiple_command.c                       /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 22:14:11 by adandres               /    /  /         */
/*   Updated: 2020/06/21 11:57:45 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int		is_command(char *input, int i, int sep)
{
	if (input[i] == '\n' && (i - sep > 0 || (i == 1 && sep == 0)))
		return (1);
	return (0);
}

static int		count_command(char *input)
{
	int	i;
	int	sep;
	int	count;
	int	quotes;

	i = 0;
	sep = 0;
	quotes = 0;
	count = 0;
	while (input[i])
	{
		quotes = check_quotes(input[i], quotes);
		if (is_command(input, i, sep) && quotes == 0)
		{
			count += 1;
			sep = i + 1;
		}
		else if (input[i] == '\n' && quotes == 0)
			sep = i + 1;
		i++;
	}
	if (quotes == 0 && i - sep > 0 && sep != 0)
		count++;
	return (count);
}

static void		split_command(t_state **machine, int count)
{
	int	i;
	int	j;
	int	sep;
	int	quotes;
	char	*input;

	i = 0;
	j = 0;
	sep = 0;
	quotes = 0;
	input = (*machine)->cmd;
	(*machine)->cmd_tab = (char**)malloc(sizeof(char *) * (count + 1));
	while (input[i])
	{
		quotes = check_quotes(input[i], quotes);
		if (is_command(input, i, sep) && quotes == 0)
		{
			(*machine)->cmd_tab[j] = my_strndup(input + sep, i - sep);
			sep = i + 1;
			j++;
		}
		else if (input[i] == '\n' && quotes == 0)
			sep = i + 1;
		i++;
	}
	if (i - sep >= 0 && quotes == 0)
	{
		(*machine)->cmd_tab[j] = my_strndup(input + sep, i - sep);
		j++;
	}
	(*machine)->cmd_tab[j] = NULL;
}

void		handle_multiple_command(t_state **machine)
{
	int	count;

	count = count_command((*machine)->cmd);
	if (count == 0)
		return;
	split_command(machine, count);
	free((*machine)->cmd);
	(*machine)->cmd = my_strdup((*machine)->cmd_tab[0]);
	(*machine)->cmd_tab_i = 1;
	(*machine)->cmd_tab_len = count;
}

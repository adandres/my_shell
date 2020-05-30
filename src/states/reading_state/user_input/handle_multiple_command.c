/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   handle_multiple_command.c                       /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 22:14:11 by adandres               /    /  /         */
/*   Updated: 2020/05/30 16:42:32 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int		count_command(char *input)
{
	int	i;
	int	count;
	int	quotes;

	i = 0;
	quotes = 0;
	count = 0;
	while (input[i])
	{
		quotes = check_quotes(input[i], quotes);
		if (quotes == 0 && input[i] == '\n' && i != 0 && input[i - 1] != '\n')
			count++;
		i++;
	}
	return (count);
}

static void		split_command(t_state **machine, int count)
{
	int	i;
	int	j;
	int	sep;
	int	e;
	int	quotes;
	char	*input;

	i = 0;
	j = 0;
	sep = 0;
	quotes = 0;
	e = 0;
	input = (*machine)->cmd;
	(*machine)->cmd_tab = (char**)malloc(sizeof(char *) * (count + 1));
	while (input[i])
	{
		quotes = check_quotes(input[i], quotes);
	if ((input[i] == '\n' && quotes == 0 && i - sep > 1) || input[i + 1] == '\0')
		{
			if (input[i + 1] == '\0')
				e = 1;
			(*machine)->cmd_tab[j] = my_strndup(input + sep, i - sep + e);
			sep = i + 1;
			j++;
		}
		i++;
	}
	(*machine)->cmd_tab[j] = NULL;
}

void		handle_multiple_command(t_state **machine)
{
	int	count;

	count = count_command((*machine)->cmd);
	if (count == 0)
		return;
	count += 1;
	split_command(machine, count);
	free((*machine)->cmd);
	(*machine)->cmd = my_strdup((*machine)->cmd_tab[0]);
	(*machine)->cmd_tab_i = 1;
	(*machine)->cmd_tab_len = count;
}

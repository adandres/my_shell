/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   parse_input.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 01:12:23 by adandres               /    /  /         */
/*   Updated: 2020/05/22 14:19:57 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	parser(char *input, t_list **token_list);
void	sort_token(t_list **token_list, int is_debug);

static char	*dump_comment(char *input)
{
	int	i;
	int	quotes;
	char	*new;

	i = 0;
	new = NULL;
	quotes = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && \
			(quotes == 0 || quotes == input[i]))
			quotes = ((quotes == 0) ? input[i] : 0);
		if (quotes == 0 && input[i] == '#')
		{
			if (i != 0)
				new = my_strndup(input, i);
			free(input);
			return (new);
		}
		i++;
	}
	return (input);
}

static int	is_quoted(char *input)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (input && input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && \
			(quotes == 0 || quotes == input[i]))
			quotes = ((quotes == 0) ? input[i] : 0);
		i++;
	}
	return (quotes);
}

int		wrong_input(t_state **machine)
{
	if (is_quoted((*machine)->cmd))
	{
		if ((*machine)->file_fd == -1)
			re_read_input(machine);
		else
			re_read_file(machine);
		return (1);
	}
	if (!((*machine)->cmd = dump_comment((*machine)->cmd)))
	{
		(*machine)->state = READ;
		return (1);
	}
	return (0);
}

void		parse_input(t_state **machine)
{
	t_list	*list;

	list = NULL;
	if ((*machine)->is_debug)
		printf("\n--------    Start_parsing    --------\n\n\n");
	if (wrong_input(machine))
		return;	
	(*machine)->state = BUILD;
	parser((*machine)->cmd, &list);
	if (list)
	{
		sort_token(&list, (*machine)->is_debug);
		(*machine)->token_list = list;
		write_hdoc(machine);
		return;
	}
	(*machine)->state = READ;
	free((*machine)->cmd);
	if ((*machine)->file_fd > 0)
		exit(EXIT_FAILURE);
}

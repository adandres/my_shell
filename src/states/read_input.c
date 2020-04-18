/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   read_input.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 18:22:49 by adandres               /    /  /         */
/*   Updated: 2020/04/17 20:03:06 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char		*get_cmd(void)
{
	int	ret;
	char	*cmd;

	cmd = NULL;
	if ((ret = get_next_line(0, &cmd)) <= 0)
		return (NULL);
	if (my_strlen(cmd) == 0)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

char		*re_read_input(void)
{
	char	*cmd;
	char	*input;

	my_printf("> ");
	input = my_strdup("\n");
	cmd = get_cmd();
	input = my_strjoin_free(input, cmd);
	free(cmd);
	return (input);
}

void		read_input(t_state **machine)
{
	if (isatty(STDIN_FILENO))
		my_printf("$> ");
	if (((*machine)->cmd = get_cmd()) != NULL)
		(*machine)->state = PARSE;
	else if (isatty(0) == 0)
		exit(EXIT_SUCCESS);
}

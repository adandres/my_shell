/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   read_input.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 18:22:49 by adandres               /    /  /         */
/*   Updated: 2020/06/15 14:31:31 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

t_hterm		*init_term_handling_struct(t_state *machine)
{
	t_hterm		*hterm;

	if (!(hterm = (t_hterm*)malloc(sizeof(t_hterm))))
		return (NULL);
	hterm->history = machine->history;
	hterm->h_len = my_tablen(hterm->history);
	hterm->pos = 0;
	hterm->save = NULL;
	hterm->curs = 0;
	hterm->hist = -1;
	hterm->restart = 0;
	return (hterm);
}

char		*get_input(t_state *machine)
{
	t_hterm *hterm;
	char	*input;

	my_printf("> ");
	hterm = init_term_handling_struct(machine);
	get_cmd(&hterm);
	input = hterm->cmd;
	free(hterm);
	return (input);
}

void		re_read_input(t_state **machine)
{
	char	*input;
	t_hterm	*hterm;

	hterm = init_term_handling_struct(*machine);
	input = NULL;
	my_printf("> ");
	if ((*machine)->cmd)
		input = my_strjoin_free((*machine)->cmd, "\n");
	get_cmd(&hterm);
	(*machine)->history = hterm->history;
	if (hterm->pos == 0)
		;
	else if (input)
		input = my_strjoin_free(input, hterm->cmd);
	else
		input = my_strdup(hterm->cmd);
	if (hterm->save)
		free(hterm->save);
	free(hterm->cmd);
	free(hterm);
	(*machine)->cmd = input;
	if (hterm->pos != 0)
		handle_multiple_command(machine);
}

void		reset_line(void)
{
	my_printf("\x1b[2K");
	my_printf("\x1b[%dD", 3);
}

void		read_input(t_state **machine)
{
	t_hterm		*hterm;

	if ((*machine)->cmd_tab_len != 0)
	{
		(*machine)->cmd = my_strdup((*machine)->cmd_tab[(*machine)->cmd_tab_i]);
		(*machine)->cmd_tab_i += 1;
		if ((*machine)->cmd_tab_i == (*machine)->cmd_tab_len)
		{
			(*machine)->cmd_tab_len = 0;
			(*machine)->cmd_tab_i = 0;
			free_tab((*machine)->cmd_tab);
		}
		(*machine)->state = PARSE;
		return;
	}
	reset_line();
	hterm = init_term_handling_struct(*machine);
	if (isatty(STDIN_FILENO))
		my_printf("$> ");
	get_cmd(&hterm);
	(*machine)->cmd = hterm->cmd;
	(*machine)->history = hterm->history;
	if (hterm->save)
		free(hterm->save);
	free(hterm);
	handle_multiple_command(machine);
	if ((*machine)->cmd != NULL)
		(*machine)->state = PARSE;
	else if (isatty(0) == 0)
		exit(EXIT_SUCCESS);
}

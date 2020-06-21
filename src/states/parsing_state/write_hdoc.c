/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   write_hdoc.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/18 17:54:25 by adandres               /    /  /         */
/*   Updated: 2020/06/21 13:25:25 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char	*get_input(t_state *machine);

void	pop_hdoc(t_redir **redir, char  *stop, t_state *machine)
{
	char	*input;
	int	i;
	int	fd;
	int	fds[2];

	i = 0;
	pipe(fds);
	fd = fds[1];
	if (machine->file_fd == -1)
		input = get_input(machine);
	else
	{
		re_read_file(&machine);
		input = machine->cmd;
	}
	while (my_strcmp(input, stop) != 0)
	{
		printf("%s -%s\n", input, stop);
		my_putendl_fd(input, fds[1]);
		free(input);
		if (machine->file_fd == -1)
			input = get_input(machine);
		else
		{
			re_read_file(&machine);
			input = machine->cmd;
		}
	}
	free(input);
	close(fd);
	(*redir)->hdoc = fds[0];
}

void	write_hdoc(t_state **machine)
{
	t_token		*token;
	t_token		*stop;
	t_list		*list;

	my_lst_reverse(&(*machine)->token_list);
	list = (*machine)->token_list;
	while (list)
	{
		token = list->content;
		if (token->type == R_DOC)
		{
			stop = list->next->content;
			pop_hdoc((t_redir**)&token->content, stop->content, *machine);
		}
		list = list->next;
	}
	my_lst_reverse(&(*machine)->token_list);
}

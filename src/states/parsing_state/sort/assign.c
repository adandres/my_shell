/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   assign.c                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/22 16:14:32 by adandres               /    /  /         */
/*   Updated: 2020/04/22 16:14:55 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	check_parser(int type, int prev_type, int is_cmd)
{
	if (type == WORD && prev_type / 10 == REDIR)
		type = FILENAME;
	else if (type == WORD && is_cmd == 0)
		type = CMD;
	else if (type == WORD || (type == VAR && is_cmd == 1))
		type = ARG;
	return (type);
}

void	assign_word(t_list **token_list)
{
	t_token		*token;
	t_list		*list;
	int		prev_type;
	int		is_cmd;

	prev_type = 0;
	is_cmd = 0;
	list = *token_list;
	while (list)
	{
		token = list->content;
		token->type = check_parser(token->type, prev_type, is_cmd);
		if (token->type == PIPE || token->type < REDIR * 10)
			is_cmd = 0;
		if (token->type == CMD)
			is_cmd = 1;
		prev_type = token->type;
		list = list->next;
	}
}



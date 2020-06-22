/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   assign.c                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/22 16:14:32 by adandres               /    /  /         */
/*   Updated: 2020/06/22 13:11:53 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	check_parser(int type, int prev_type, int is_cmd)
{
	if (type == WORD && prev_type / 10 == REDIR)
		type = FILENAME;
	else if (type == WORD && is_cmd == 0)
		type = CMD;
	else if (type == WORD || (type == VAR && is_cmd))
		type = ARG;
	else if (type == SENV && is_cmd)
		type = ARG;
	return (type);
}

void	assign_word(t_list **token_list)
{
	t_token		*token;
	t_list		*list;
	t_token		*first;
	int		prev_type;
	int		is_cmd;

	prev_type = 0;
	is_cmd = 0;
	list = *token_list;
	first = list->content;
	while (list)
	{
		token = list->content;
		if (token->type == PIPE || token->type < REDIR * 10)
		{
			if (is_cmd == 0 && first->type == SENV)
				first->type = CMD;
			is_cmd = 0;
			first = token;
		}
		token->type = check_parser(token->type, prev_type, is_cmd);
		if (token->type == CMD)
			is_cmd = 1;
		prev_type = token->type;
		list = list->next;
	}
	if (is_cmd == 0 && token->type >= REDIR * 10 && first->type == SENV)
		first->type = CMD;
}

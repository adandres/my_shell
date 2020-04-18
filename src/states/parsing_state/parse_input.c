/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   parse_input.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 01:12:23 by adandres               /    /  /         */
/*   Updated: 2020/04/19 01:20:25 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	add_token(t_list **token_list, t_token *token)
{
	t_list		*new_token;

	new_token = (t_list*)malloc(sizeof(t_list));
	new_token->content = token;
	new_token->next = *token_list;
	*token_list = new_token;
}

int	check_parser(int type, int prev_type, int is_cmd)
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
	int			prev_type;
	int			is_cmd;

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

void	sort_token(t_list **token_list, int is_debug)
{
	my_lst_reverse(token_list);
	if (is_debug){printf("input_list: "); print_list(*token_list, 0); printf("type__list: "); print_list(*token_list, 1);printf("\n");}
	assign_word(token_list);
	if (is_debug){printf("input_list: "); print_list(*token_list, 0); printf("type__list: "); print_list(*token_list, 1);printf("\n");}
	first_is_cmd(token_list);
	if (is_debug){printf("input_list: "); print_list(*token_list, 0); printf("type__list: "); print_list(*token_list, 1);printf("\n");}
	sort_list(token_list);
	if (is_debug){printf("input_list: "); print_list(*token_list, 0); printf("type__list: "); print_list(*token_list, 1);printf("\n");}
	reverse_redir(token_list);
	if (is_debug){printf("input_list: "); print_list(*token_list, 0); printf("type__list: "); print_list(*token_list, 1);printf("\n");}
	my_lst_reverse(token_list);
}

void	parser(char *input, t_list **token_list)
{
	t_token	*token;
	int	len;
	int	last;
	int	i;

	i = 0;
	last = 0;
	while (input[i] != '\0')
	{
		if (input[i] != ' ')
		{
			if ((len = get_token(&token, input + i, last)) == -1)
			{
				free_tlist(*token_list);
				return ;
			}
			last = token->type;
			add_token(token_list, token);
			i += len - 1;
		}
		i++;
	}
}

void		parse_input(t_state **machine)
{
	t_list	*list;

	list = NULL;
	if ((*machine)->is_debug)
		printf("\n--------    Start_parsing    --------\n\n\n");
	parser((*machine)->cmd, &list);
	if (list == NULL)
	{
		(*machine)->state = READ;
		return ;
	}
	else
		(*machine)->state = EXPAND;
	sort_token(&list, (*machine)->is_debug);
	(*machine)->token_list = list;
}

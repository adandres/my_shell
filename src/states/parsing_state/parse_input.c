/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   parse_input.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 01:12:23 by adandres               /    /  /         */
/*   Updated: 2020/04/21 19:12:09 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void	add_token(t_list **token_list, t_token *token)
{
	t_list		*new_token;

	if (!(new_token = (t_list*)malloc(sizeof(t_list))))
		no_mem_error();
	new_token->content = token;
	new_token->next = *token_list;
	*token_list = new_token;
}

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

static void	assign_word(t_list **token_list)
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

static void	sort_token(t_list **token_list, int is_debug)
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

static void	parser(char *input, t_list **token_list)
{
	t_token	*token;
	int	len;
	int	last;
	int	i;

	i = 0;
	last = 0;
	while (input[i] != '\0')
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
		{
				printf("----\n\n%s\n\n\n", input + i);
			if ((len = get_token(&token, input + i, last)) != -1)
			{
				last = token->type;
				add_token(token_list, token);
				i += len - 1;
			}
			else
			{
				if (token)
				{
					free(token->data);
					free(token);
					token = NULL;
				}
				free_tlist(*token_list);
				*token_list = NULL;
				return;
			}
		}
		i++;
	}
}

char		*dump_comment(char *input)
{
	int	i;
	int	quotes;
	char	*new;

	i = 0;
	quotes = 0;
	if (input[0] == '#')
	{
		free(input);
		return (NULL);
	}
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && \
			(quotes == 0 || quotes == input[i]))
			quotes = ((quotes == 0) ? input[i] : 0);
		if (quotes == 0 && input[i] == '#')
			break;
		i++;
	}
	if (input[i] == '#')
	{
		new = my_strndup(input, i);
		free(input);
		return (new);
	}
	return (input);
}

void		parse_input(t_state **machine)
{
	t_list	*list;

	list = NULL;
	(*machine)->count++;
	printf("count: %d\n", (*machine)->count);
	if ((*machine)->is_debug)
		printf("\n--------    Start_parsing    --------\n\n\n");
	printf("--------CMD--------\n\n ---\n%s\n---\n\n\n", (*machine)->cmd);
	if (!((*machine)->cmd = dump_comment((*machine)->cmd)))
	{
		(*machine)->state = READ;
		return ;
	}
	parser((*machine)->cmd, &list);
	if ((*machine)->count >= 5)
		while (1);
	if (list == NULL)
	{
		if ((*machine)->cmd)
		{
			free((*machine)->cmd);
			/*if ((*machine)->file_fd > 0)
				exit(EXIT_FAILURE);*/
		}
		(*machine)->state = READ;
		return;
	}
	else
		(*machine)->state = EXPAND;
	sort_token(&list, (*machine)->is_debug);
	(*machine)->token_list = list;
}

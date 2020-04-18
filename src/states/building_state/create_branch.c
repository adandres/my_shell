/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   create_branch.c                                 /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 20:21:33 by adandres               /    /  /         */
/*   Updated: 2020/04/18 19:45:05 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int			builtin(char *input)
{
	if (my_strcmp(input, "cd") == 0)
		return (CD);
	if (my_strcmp(input, "unset") == 0)
		return (UNSET);
	if (my_strcmp(input, "set") == 0 || my_strchr(input, '='))
		return (SET);
	if (my_strcmp(input, "env") == 0)
		return (ENV);
	if (my_strcmp(input, "echo") == 0)
		return (BECHO);
	if (my_strcmp(input, "exit") == 0)
		return (EXIT);
	if (my_strcmp(input, "export") == 0)
		return (EXPORT);
	return (-1);
}

t_ast	*create_node(void *data, int state)
{
	t_ast		*new;

	new = (t_ast*)malloc(sizeof(t_ast));
	new->data = data;
	new->type = state;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

char	**grep_argv(t_list *token_list)
{
	t_token *token;
	char **argv;
	int i;

	argv = (char**)malloc(sizeof(char*) * (my_lst_len(token_list) + 1));
	i = 0;
	while (token_list)
	{
		token = token_list->content;
		if (token->type != CMD && token->type != ARG)
			break;
		argv[i] = my_strdup(token->data);
		token_list = token_list->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

t_ast	*create_func_node(t_list *token_list)
{
	t_cmd		*cmd;
	t_ast		*new;

	new = NULL;
	my_lst_reverse(&token_list);
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	cmd->argv = grep_argv(token_list);
	cmd->path = NULL;
	cmd->builtin = builtin(cmd->argv[0]);
	new = create_node(cmd, CMD);
	my_lst_reverse(&token_list);
	return (new);
}

t_ast	*create_branch(t_list *token_list, int state)
{
	t_token		*token;
	t_ast		*ast;

	token = token_list->content;
	if (state != COMMAND)
		return (create_node(token->data, token->type));
	if (token->type == CMD || token->type == ARG)
	{
		ast = create_func_node(token_list);
		return (ast);
	}
	return (create_node(token->data, token->type));
}

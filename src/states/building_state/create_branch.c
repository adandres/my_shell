/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   create_branch.c                                 /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 20:21:33 by adandres               /    /  /         */
/*   Updated: 2020/04/21 14:37:44 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int		is_set(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '=')
	{
		if (my_isalpha(input[i]) || input[i] == '_')
			i++;
		else
			return (0); 
	}
	if (input[i] == '=' && i != 0)
		return (1);
	return (0);
}

static int		builtin(char *input)
{
	if (my_strcmp(input, "cd") == 0)
		return (CD);
	if (my_strcmp(input, "unset") == 0)
		return (UNSET);
	if (my_strcmp(input, "set") == 0 || is_set(input))
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

static t_ast	*create_node(void *data, int state)
{
	t_ast		*new;

	new = (t_ast*)malloc(sizeof(t_ast));
	new->data = data;
	new->type = state;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

static char	**grep_argv(t_list *token_list)
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

static t_ast	*create_func_node(t_list *token_list)
{
	t_cmd		*cmd;
	t_ast		*new;
	int		type;

	new = NULL;
	type = CMD;
	my_lst_reverse(&token_list);
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	cmd->argv = grep_argv(token_list);
	cmd->path = NULL;
	if ((cmd->builtin = builtin(cmd->argv[0])) >= 0)
		type = BUILT;
	new = create_node(cmd, type);
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

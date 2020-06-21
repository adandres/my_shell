/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   expand_redir.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/22 17:55:22 by adandres               /    /  /         */
/*   Updated: 2020/06/21 13:24:43 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	default_redir(int type)
{
	if (type == R_OUT || type == RA_OUT || type == R_ER || type == R_OCL)
		return (1);
	if (type == R_IN || type == R_RW || type == R_ICL || type == R_DOC)
		return (0);
	return (-1);
}

static int pass_number(char *input)
{
	int i;

	i = 0;
	while (input[i] >= '0' && input[i] <= '9')
		i++;
	return (i);
}

static int	pass_type(int type)
{
	if (type == R_DOC || type == RA_OUT || type == R_RW || type == R_ER)
		return (2);
	return (1);
}

static int	pass(char *input, int type)
{
	int	i;

	i = pass_number(input);
	i += pass_type(type);
	return (i);
}

static t_redir		*get_redir(char *input, int type)
{
	t_redir *redir;

	redir = (t_redir*)malloc(sizeof(t_redir));
	redir->fd = default_redir(type);
	if (input[0] >= '0' && input[0] <= '9')
		redir->fd = my_atoi(input);
	redir->copy = 0;
	return (redir);
}

t_token		*expand(t_token *token)
{
	t_redir		*redir;
	char		*input;
	int		i;

	input = token->content;
	redir = get_redir(input, token->type);
	i = pass(input, token->type);
	if (input[i] && input[i] == '&' && token->type != R_ICL && \
			token->type != R_OCL && token->type != R_DOC)
	{
		token->type = R_CP;
		redir->copy = 1;
	}
	token->content = redir;
	free(input);
	return (token);
}

void	expand_redir(t_list **token_list)
{
	t_list		*list;
	t_token		*token;

	token = NULL;
	list = *token_list;
	while (list)
	{
		token = list->content;
		if (token->type / 10 == REDIR)
			token = expand(token);
		list->content = token;
		list = list->next;
	}
}

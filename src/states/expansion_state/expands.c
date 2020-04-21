/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   expands.c                                       /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/07 23:21:25 by adandres               /    /  /         */
/*   Updated: 2020/04/19 02:08:32 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	default_redir(int type)
{
	if (type == R_OUT || type == RA_OUT || type == R_ER || type == R_OCL)
		return (1);
	if (type == R_IN || type == R_RW || type == R_ICL)
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

	input = token->data;
	redir = get_redir(input, token->type);
	i = pass(input, token->type);
	if (input[i] && input[i] == '&' && token->type != R_ICL && token->type != R_OCL)
	{
		token->type = R_CP;
		redir->copy = 1;
	}
	token->data = redir;
	free(input);
	return (token);
}

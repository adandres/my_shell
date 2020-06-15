/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   parser.c                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/22 16:16:13 by adandres               /    /  /         */
/*   Updated: 2020/05/31 15:34:40 by adandres                                 */
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

static int	get_next_token(char *input, t_list **token_list, int *last)
{
	t_token *token;
	int	len;

	len = -1;
	token = NULL;
	if ((len = get_token(&token, input, *last)) != -1)
	{
		*last = token->type;
		add_token(token_list, token);
		return (len);
	}
	else
	{
		
		printf("shell: %s: error parsing\n", input);
		free_token(token);
		free_tlist(*token_list);
		*token_list = NULL;
		return (-1);
	}
	return (len);
}

void	parser(char *input, t_list **token_list)
{
	int	len;
	int	last;
	int	i;

	i = 0;
	last = 0;
	while (input[i] != '\0')
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
		{
			if ((len = get_next_token(input + i, token_list, &last)) == -1)
				return;
			i += len - 1;
		}
		i++;
	}
}

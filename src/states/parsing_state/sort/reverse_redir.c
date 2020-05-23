/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   reverse_redir.c                                 /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 19:57:42 by adandres               /    /  /         */
/*   Updated: 2020/04/26 15:06:26 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	my_spe_lst_len(t_list *list)
{
	t_token	*token;
	int i;

	i = 0;
	while (list)
	{
		token = list->content;
		if (token->type / 10 < REDIR || token->type == PIPE)
			break;
		list = list->next;
		i++;
	}
	return (i);
}

static int check(t_token *token, t_token *n_token)
{
	if ((token->type / 10 == REDIR) && (n_token->type / 10 == REDIR) && token->type)
		return (1);
	return (0);
}

static int swap(t_list **current, int to_pass)
{
	t_list	*next;

	next = my_lst_pass(*current, to_pass);
	if (check((*current)->content, next->content))
	{
		my_memswap(&(*current)->content, &next->content);
		*current = (*current)->next;
		next = next->next;
		my_memswap(&(*current)->content, &next->content);	
		return (1);
	}
	return (0);
}

static int check_reset(t_token *token)
{
	if (token->type / 10 < REDIR || token->type == PIPE)
		return (1);
	return (0);
}

void	reverse_redir(t_list **token_list)
{
	t_list  *current;
	int	to_pass;
	int	i;

	i = 0;
	current = *token_list;
	while (current != NULL)
	{
		if (check_reset(current->content) == 1)
			i = 0;
		if ((to_pass = my_spe_lst_len(current) - (i * 2) - 2) > 0)
			i += swap(&current, to_pass);
		current = current->next;
	}
}

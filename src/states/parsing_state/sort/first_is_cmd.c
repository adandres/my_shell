/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   first_is_cmd.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 19:59:03 by adandres               /    /  /         */
/*   Updated: 2020/06/22 18:34:45 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void	swap(t_list **list, t_list **head, t_list *prev, t_list *curr)
{
	if (*head == NULL)
	{
		prev->next = curr->next;
		curr->next = *list;
		*list = curr;
	}
	else
	{
		prev->next = curr->next;
		curr->next = (*head)->next;
		(*head)->next = curr;
	}
}

static int	check_command(t_token *token, int mode)
{
	if (token->type == CMD && mode == 1)
		return (1);
	if (token->type == SENV && mode == 0)
		return (1);
	return (0);
}

static int	check_del(t_token *token)
{
	if ((token->type == PIPE || token->type / 10 < REDIR))
		return (1);
	if (token->type == SENV)
		return (1);
	return (0);
}

void	first_is_cmd(t_list **list, int mode)
{
	t_list	*head;
	t_list	*curr;
	t_list	*prev;
	int	j;

	j = 0;
	curr = *list;
	prev = curr;
	head = NULL;
	while (curr)
	{
		if (check_command(curr->content, mode) && j != 0)
			swap(list, &head, prev, curr);
		if (check_del(curr->content))
		{
			head = curr;
			j = -1;
		}
		j++;
		prev = curr;
		curr = curr->next;
	}
	if (mode == 0)
		first_is_cmd(list, 1);
}

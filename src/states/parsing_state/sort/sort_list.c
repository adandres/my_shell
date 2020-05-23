/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   sort_list.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 20:00:16 by adandres               /    /  /         */
/*   Updated: 2020/04/18 23:17:34 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	check_type(t_token *token)
{
	if (token->type / 10 == REDIR || token->type == FILENAME)
		return (1);
	return (0);
}

void	switch_token(t_list **keep, t_list *list)
{
	t_list *tmp;
	t_list *r_file;

	tmp = (*keep)->next;
	r_file = (*keep)->next;
	while (r_file)
	{
		if (check_type(r_file->next->content))
			r_file = r_file->next;
		else
			break;
	}
	r_file->next = list->next;
	(*keep)->next = list;
	*keep = (*keep)->next;
	(*keep)->next = tmp;
}

void	sort_list(t_list **token_list)
{
	t_token	*token;
	t_list	*list;
	t_list	*keep;
	int	last;

	last = 0;
	list = *token_list;
	while (list != NULL)
	{
		token = list->content;
		if (token->type == CMD || (last != FILENAME && token->type == ARG))
			keep = list;
		if (last == FILENAME && token->type == ARG)
			switch_token(&keep, list);
		last = token->type;
		list = list->next;
	}
}

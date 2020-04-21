/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   expand_input.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 20:10:10 by adandres               /    /  /         */
/*   Updated: 2020/04/19 02:08:25 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	expand_token(t_list **token_list)
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

void	expand_input(t_state **machine)
{
	if ((*machine)->is_debug)
		printf("\n--------    Start_expansion    --------\n\n");
	expand_token(&(*machine)->token_list);
	if ((*machine)->is_debug)
	{
		my_lst_reverse(&(*machine)->token_list);
		printf("input_list: ");
		print_list((*machine)->token_list, 0);
		printf("type__list: ");
		print_list((*machine)->token_list, 1);
		my_lst_reverse(&(*machine)->token_list);
	}
	(*machine)->state = BUILD;
}

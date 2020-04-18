/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   build_tree.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 20:14:11 by adandres               /    /  /         */
/*   Updated: 2020/04/17 20:04:08 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"


t_ast   *parse_cmd(t_state *machine);
t_ast	*create_branch(t_list *token_list, int state, t_state *machine);

t_token		*copy_token(t_token *token)
{
	t_token		*new;

	new = (t_token*)malloc(sizeof(t_token));
	new->data = token->data;
	new->type = token->type;
	return (new);
}

void	add_list(t_list **tail, t_list *head)
{
	t_list *tmp;

	tmp = (t_list*)malloc(sizeof(t_list));
	tmp->content = copy_token(head->content);
	tmp->next = *tail;
	*tail = tmp;
}

static int check(t_token *token, int state)
{
	if ((token->type / 10) == state || (state == REDIR && token->type == PIPE))
		return (1);
	return (0);
}



void	free_list(t_list *list)
{
	t_list *next;

	while (list)
	{
		next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
}
t_ast	*build_tree(t_list *token_list, int state, t_state *machine);

t_ast	*get_root(t_list *head, t_list *tail, int state, t_state *machine)
{
	t_ast	*root;
	
	root = create_branch(head, state, machine);
	if (state != COMMAND)
	{
		if (head->next)
			root->left = build_tree(head->next, state, machine);
		else
			root->left = NULL;
		my_lst_reverse(&tail);
		if (tail)
			root->right = build_tree(tail, state, machine);
		else
			root->right = NULL;
	}
	if (tail)
	free_list(tail);
	return (root);

}

t_ast	*build_tree(t_list *token_list, int state, t_state *machine)
{
	t_ast		*root;
	t_list		*head;
	t_list		*tail;

	head = token_list;
	tail = NULL;
	root = NULL;
	while (head != NULL)
	{
		if (check(head->content, state))
		{
			root = get_root(head, tail, state, machine);
			return (root);
		}
		add_list(&tail, head);
		head = head->next;
	}
	if (tail)
	free_list(tail);
	if (state < COMMAND)
		root = build_tree(token_list, state + 1, machine);
	return (root);
}

void            build_state(t_state **machine)
{
        if ((*machine)->is_debug)
		printf("\n --------    Start_building    --------\n\n\n");
        (*machine)->tree = build_tree((*machine)->token_list, 0, *machine);
        (*machine)->state = EXEC;
        if ((*machine)->is_debug)
		print_tree((*machine)->tree, 0);
}

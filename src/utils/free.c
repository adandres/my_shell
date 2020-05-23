/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   free.c                                          /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/15 12:17:28 by adandres               /    /  /         */
/*   Updated: 2020/05/23 19:18:47 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	free_token(t_token *token)
{
	if (token == NULL)
		return;
	if (token->data)
		free(token->data);
	free(token);
}

void	free_tlist(t_list *token_list)
{
	t_list *next;

	if (token_list == NULL)
		return;
	while (token_list)
	{
		free_token(token_list->content);
		next = token_list->next;
		free(token_list);
		token_list = next;
	}
}

void	free_leaf(t_cmd *cmd)
{
	if (cmd == NULL)
		return;
	if (cmd->path)
		free(cmd->path);
	if (cmd->argv)
		free_tab(cmd->argv);
	free(cmd);
}

void	free_tree(t_ast *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		free_tree(tree->left);
	if (tree->type == BUILT || tree->type == CMD || tree->type == NUL)
		free_leaf(tree->data);
	if (tree->right)
		free_tree(tree->right);
	free(tree);
}



void	reset(t_state *machine)
{
	if (machine->cmd)
		free(machine->cmd);
	machine->cmd = NULL;
	free_tree(machine->tree);
	machine->tree = NULL;
	free_tlist(machine->token_list);
	machine->token_list = NULL;
}

void	free_all(t_state *machine)
{
	reset(machine);
	free_tab(machine->my_env);
	free_tab(machine->history);
	free(machine);
}

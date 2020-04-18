/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   free.c                                          /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/15 12:17:28 by adandres               /    /  /         */
/*   Updated: 2020/04/17 20:11:33 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	free_tlist(t_list *token_list)
{
	t_list *next;
	t_token *token;

	while (token_list)
	{
		token = token_list->content;
		free(token->data);
		free(token);
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
	if (tree->type == BUILT || tree->type == CMD)
		free_leaf(tree->data);
	if (tree->right)
		free_tree(tree->right);
	free(tree);
	tree = NULL;
}

void	reset(t_state *machine)
{
	free(machine->cmd);
	free_tree(machine->tree);
	free_tlist(machine->token_list);
}

void	free_all(t_state *machine)
{
	reset(machine);
	free_tab(machine->my_env);
	free(machine);
}
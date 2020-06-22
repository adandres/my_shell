/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   print_tree.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 21:16:54 by adandres               /    /  /         */
/*   Updated: 2020/06/22 12:18:45 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void padding(char ch, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		my_putchar(ch);
		i++;
	}
}

void	print_tree(t_ast *root, int level)
{
	char	*value;
	t_cmd	*cmd;
	t_redir *redir;

	char	**tab;

	if (root == NULL)
	{
		padding ('\t', level + 1);
		my_putendl("~");
	}
	else
	{
		if (root->type == CMD)
		{
			cmd = (t_cmd*)root->data;
			tab = cmd->argv;
			value = tab[0];
		}
		else if (root->type / 10 != REDIR)
			value = root->data;
		else
		{
			redir = root->data;
			value = redir->input;//my_itoa(root->type);
		
		}
		print_tree(root->right, level + 1);
		padding('\t', level + 1);
		my_printf("%s\n", value);
		print_tree(root->left, level + 1);
		if (root->type / 10 == REDIR)
			free(value);
	}
}

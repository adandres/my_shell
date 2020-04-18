/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   execute_tree.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/07 21:21:47 by adandres               /    /  /         */
/*   Updated: 2020/04/17 22:38:18 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

t_return	*init_ret(void)
{
	t_return	*ret;

	ret = (t_return*)malloc(sizeof(t_return));
	ret->n_proc = 0;
	ret->n_file = 0;
	ret->n_copy = 0;
	ret->status = 0;
	ret->fd_out = dup(STDOUT_FILENO);
	return (ret);
}

void		free_leaf(t_cmd *cmd);

int		exec_builtin(t_state **machine, t_cmd *cmd, int built)
{
	static int	(*builtin_func[7])(char **argv, t_state **machine) = \
	{&exit_prog, &ft_echo, &change_directory, \
		&my_env, &my_unsetenv, &my_set, &my_export};


	cmd = get_cmd_data(cmd, (*machine)->my_env);
	(*machine)->status = (builtin_func[built])(cmd->argv, machine);
	free_leaf(cmd);
	return (0);
}

int		check_this(int fd, t_return *ret)
{
	int	i;

	i = 0;
	while (i < ret->n_copy)
	{
		if (ret->copy[i] == fd)
			return (ret->c_fd[i]);
		i++;
	}
	return (-1);
}

void	close_fd(t_ast *root, t_return **ret)
{
	t_redir *redir;
	int		a;

	redir = root->data;
	a = check_this(redir->fd, *ret);
	if (a != -1)
	{
		(*ret)->fd[(*ret)->n_file] = a;
		(*ret)->type[(*ret)->n_file] = root->type;
		(*ret)->n_file += 1;
	}
	(*ret)->fd[(*ret)->n_file] = redir->fd;
	(*ret)->type[(*ret)->n_file] = root->type;
	(*ret)->n_file += 1;
}

int			is_builtin(t_cmd *cmd)
{
	char	*input;

	input = cmd->argv[0];
	if (my_strcmp(input, "cd") == 0)
		return (CD);
	if (my_strcmp(input, "unset") == 0)
		return (UNSET);
	if (my_strcmp(input, "set") == 0 || my_strchr(input, '='))
		return (SET);
	if (my_strcmp(input, "env") == 0)
		return (ENV);
	if (my_strcmp(input, "echo") == 0)
		return (BECHO);
	if (my_strcmp(input, "exit") == 0)
		return (EXIT);
	if (my_strcmp(input, "export") == 0)
		return (EXPORT);
	return (-1);
}


void    exec_loop(t_ast *root, t_state **machine, t_return **ret, int r_type);

void	exec_loop_next(t_ast *root, t_state **machine, t_return **ret, int r_type)
{
	if (root->type / 10 == REDIR)
	{
		if (root->type != R_ICL && root->type != R_OCL)
			redir(root, root->right, ret, root->type);
		else
			close_fd(root, ret);
		exec_loop(root->left, machine, ret, root->type);
		return ;
	}
	if ((is_builtin(root->data)) != -1 && r_type != PIPE)
	{
		exec_builtin(machine, root->data, is_builtin(root->data));
		dup2((*ret)->fd_out, 1);
	}
	else if (root->type == CMD || (is_builtin(root->data) != -1  && r_type == PIPE))
	{	exec_cmd(root, *machine, ret, r_type);
	}
	return;
}

void	exec_loop(t_ast *root, t_state **machine, t_return **ret, int r_type)
{
	if (root->type == SEMI || r_type == L_AND || r_type == L_OR)
		(*ret)->n_file = 0;
	if (root->type == SEMI)
	{
		if (root->left)
			exec_loop(root->left, machine, ret, SEMI);
		free(*ret);
		*ret = init_ret();
		if (root->right)
			exec_loop(root->right, machine, ret, SEMI);
		return;
	}
	if (root->type == L_AND || root->type == L_OR)
	{
		exec_loop(root->left, machine, ret, root->type);
		if ((!(*ret)->status && root->type == L_AND) || \
				(root->type == L_OR && (*ret)->status))
			exec_loop(root->right, machine, ret, root->type);
		return ;
	}
	if (root->type == PIPE)
	{
		exec_cmd(root, *machine, ret, r_type);
		return ;
	}
	exec_loop_next(root, machine, ret, r_type);
}

void    execute_tree(t_state **machine)
{
	t_return *ret;

	if ((*machine)->is_debug)
		printf("\n--------    Start_execution    --------\n\n\n");
	ret = init_ret();
	exec_loop((*machine)->tree, machine, &ret, SEMI);
	(*machine)->status = ret->status;
	free(ret);
	reset(*machine);
	(*machine)->state = READ;
	if ((*machine)->status && (*machine)->is_debug)
		printf("\n--------    FAILURE    --------\n");
	else if ((*machine)->is_debug)
		printf("\n--------    SUCCESS    --------\n\n\n");
}

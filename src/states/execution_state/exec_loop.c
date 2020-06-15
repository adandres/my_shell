/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   exec_loop.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 13:17:02 by adandres               /    /  /         */
/*   Updated: 2020/06/04 16:10:08 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

t_return	*init_ret(void);

static int		check_this(int fd, t_return *ret)
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

static void	close_fd(t_ast *root, t_return **ret)
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

static int	check_cmd(t_ast *root, t_state **machine, t_return **ret, int r_type)
{
	if (root->type == NUL || root->type == PIPE || root->type == CMD || \
			(root->type == BUILT && r_type == PIPE))
	{
		exec_cmd(root, *machine, ret, r_type);
	}
	return (0);
}

static int 	check_built(t_ast *root, t_state **machine, t_return **ret, int r_type)
{
	if (root->type == BUILT && r_type != PIPE)
	{
		exec_builtin(machine, root->data);
		dup2((*ret)->fd_out, 1);
	}
	return (0);
}

static int	check_tredir(t_ast *root, t_state **machine, t_return **ret, int r_type)
{
	int	exist;

	exist = 1;
	if (root->type / 10 == REDIR)
	{
		if (root->type != R_ICL && root->type != R_OCL && root->right)
			exist = exec_redir(root, *machine, ret, root->type);
		else
			close_fd(root, ret);
		if (exist)
			exec_loop(root->left, machine, ret, r_type);
		return (1);
	}
	return (0);
}

static int	check_logic(t_ast *root, t_state **machine, t_return **ret, int r_type)
{
	if (root->type == L_AND || root->type == L_OR)
	{
		r_type = root->type;
		exec_loop(root->left, machine, ret, root->type);
		if ((!(*ret)->status && root->type == L_AND) || \
				(root->type == L_OR && (*ret)->status))
			exec_loop(root->right, machine, ret, root->type);
		return (1);
	}
	return (0);
}

void	close_all(void)
{
	int i;

	i = 3;
	while (i < 256)
		close(i++);
}

static int	check_semi(t_ast *root, t_state **machine, t_return **ret, int r_type)
{
	if (root->type == SEMI)
	{
		r_type = 0;
		(*ret)->n_file = 0;
		(*ret)->n_proc = 0;
		if (root->left)
			exec_loop(root->left, machine, ret, root->type);
		free(*ret);
		*ret = init_ret();
		if (root->right)
			exec_loop(root->right, machine, ret, root->type);
		return (1);
	}
	return (0);
}

void	exec_loop(t_ast *root, t_state **machine, t_return **ret, int r_type)
{
	int	index;
	int	status;
	int	(*loop[5])(t_ast*, t_state**, t_return **, int) = {&check_semi, \
		&check_logic, &check_tredir, \
			&check_built, &check_cmd};

	index = 0;
	status = 0;
	if (root == NULL)
		return;
	if (r_type == L_AND || r_type == L_OR)
		(*ret)->n_file = 0;
	if (root->type == BUILT || root->type == CMD)
		get_cmd_data(&root, *machine);
if (root->type == PIPE && (root->right->type == CMD || root->right->type == BUILT))
		get_cmd_data(&root->right, *machine);
	while (index < 5 && status == 0)
		status = loop[index++](root, machine, ret, r_type);
}

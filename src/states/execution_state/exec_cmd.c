/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   exec_cmd.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/07 21:38:34 by adandres               /    /  /         */
/*   Updated: 2020/04/21 14:40:09 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void		exec_command(t_cmd *command, t_state *machine)
{
	if (command->builtin >= 0)
		exec_builtin(&machine, command);
	else
		execve(command->path, command->argv, machine->my_env);
	exit(EXIT_SUCCESS);
}

static int	check_out(int type)
{
	if (type == R_OUT || type == RA_OUT)
		return (1);
	if (type == R_ER || type == R_RW)
		return (1);
	return (0);
}

static void	check_red(t_return *ret)
{
	int i;

	i = 0;
	while (i < ret->n_file)
	{
		if (ret->type[i] == R_IN || ret->type[i] == R_CP)
			dup2(ret->file[i], ret->fd[i]);
		if (ret->type[i] == R_ER)
			dup2(ret->file[i], 2);
		if (check_out(ret->type[i]))
			dup2(ret->file[i], ret->fd[i]);
		if (ret->type[i] == R_ICL || ret->type[i] == R_OCL)
			close(ret->fd[i]);
		i++;
	}
}

static void	check_pipe(int type, int r_type, t_return *ret, int p[2])
{
	if (type == PIPE || (type == BUILT && r_type == PIPE))
		dup2(p[0], 0);
	if (r_type == PIPE)
		dup2(ret->pipe_out[ret->n_proc - 1], 1);
}

static void	store_stdout(t_return **ret, int p[2])
{
	close(p[0]);
	(*ret)->pipe_out[(*ret)->n_proc] = p[1];
	(*ret)->n_proc += 1;
}

void	exec_cmd(t_ast *root, t_state *machine, t_return **ret, int r_type)
{
	int	p[2];
	pid_t	pid;
	t_ast	*leaf;

	//pipe(p);
	leaf = root;
	if (root->right)
		leaf = root->right;
	/*if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		exit(EXIT_SUCCESS);
		close(p[1]);
		*/if (leaf->type == NUL)
			print_no_found(leaf->data);
		/*check_red(*ret);
		check_pipe(root->type, r_type, *ret, p);
		exec_command(leaf->data, machine);
	}
	else
	{
		store_stdout(ret, p);*/
		if (root->type != CMD && root->left && root->type != NUL)
			exec_loop(root->left, &machine, ret, root->type);
		/*close(p[1]);
		wait(&(*ret)->status);
	}*/
}

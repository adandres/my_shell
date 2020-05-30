/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   exec_redir.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/07 21:35:55 by adandres               /    /  /         */
/*   Updated: 2020/05/27 00:02:38 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	is_all_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (my_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (i);
}

static int	check_exist(int copy, t_return *ret)
{
	int i;

	i = 0;
	while (i < ret->n_file)
	{
		if (ret->fd[i] == copy)
			return (1);
		i++;
	}
	return (0);
}

static int	check_copy(int copy, int r_fd, t_return **ret)
{
	int i;

	i = 0;
	while (i < (*ret)->n_file)
	{
		if ((*ret)->fd[i] == copy)
		{
			(*ret)->copy[(*ret)->n_copy] = r_fd;
			(*ret)->c_fd[(*ret)->n_copy] = copy;
			(*ret)->n_copy += 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	open_file(char *path, int type)
{
	int file_fd;

	file_fd = -1;
	if (type == RA_OUT)
		file_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == R_OUT || type == R_RW || type == R_ER)
		file_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == R_IN)
		file_fd = open(path, O_RDONLY);
	else if (type == R_DOC)
		file_fd = open("tmp", O_RDONLY);
	if (file_fd == -1)
		fprintf(stderr, "shell: %s: No such file or directory\n", path);
	return (file_fd);
}

static int	check_r_file(char *r_file, int r_fd, int r_type, t_return **ret)
{
	int     file_fd;

	file_fd = -1;
	if (is_all_num(r_file))
		file_fd = my_atoi(r_file);
	else
		return (-1);
	if (file_fd > 2 && check_exist(file_fd, *ret) == 0)
		printf("shell: %s: Bad file descriptor\n", r_file);
	else if (file_fd < 0 && (r_fd != 1 || r_type == R_IN))
		printf("sh: %s: ambiguous redirect\n", r_file);
	else if (file_fd >= 0 && file_fd <= 2)
		return (file_fd);
	else if (check_copy(file_fd, r_fd, ret))
		return (file_fd);
	return (-1);
}

int	exec_redir(t_ast *root, t_state *machine, t_return **ret, int type)
{
	int		file_fd;
	t_redir		*redir;
	t_ast *r_file;

	machine = NULL;
	r_file = root->right;
	redir = root->data;
	if (type == R_CP)
	{
		if ((file_fd = check_r_file(r_file->data, redir->fd, type, ret)) == -2)
			return (0);
	}
	if ((type != R_DOC && type != R_CP) || \
			(file_fd == -1 && redir->fd == 1 && type == R_OUT))
		file_fd = open_file(r_file->data, root->type);
	if (file_fd == -1)
		return (0);
	(*ret)->fd[(*ret)->n_file] = redir->fd;
	(*ret)->file[(*ret)->n_file] = file_fd;
	(*ret)->type[(*ret)->n_file] = type;
	if (type == R_DOC)
		(*ret)->file[(*ret)->n_file] = redir->hdoc;	
	(*ret)->n_file++;
	return (1);
}

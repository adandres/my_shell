/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_shell.h                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 17:12:43 by adandres               /    /  /         */
/*   Updated: 2020/04/21 15:56:10 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SHELL_H
# define MY_SHELL_H

# include "defines.h"
# include "libme.h"
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <termios.h>
# include <fcntl.h>
# include <limits.h>

int		g_signal;

typedef enum	e_states
{
	ST_READ,
	ST_PARSE,
	ST_EXPAND,
	ST_BUILD,
	ST_EXEC,
	ST_END,
}		t_states;

typedef struct	s_token
{
	int	type;
	void	*data;
}		t_token;

typedef struct	s_cmd
{
	char	*path;
	char	**argv;
	int	builtin;
}		t_cmd;

typedef struct	s_redir
{
	int	fd;
	int	copy;
	int	close;
}		t_redir;

typedef struct	s_var
{
	char *name;
	char *value;
}		t_var;

typedef struct	s_return
{
	int		n_copy;
	int		copy[256];
	int		c_fd[256];
	int		n_proc;
	int		pipe_out[256];
	int		n_file;
	int		file[256];
	int		fd[256];
	int		type[256];
	int		status;
	int		fd_out;
}		t_return;

typedef struct	s_ast
{
	int		type;
	void		*data;
	struct s_ast	*left;
	struct s_ast	*right;
}		t_ast;

typedef struct	s_error
{
	char	*message;
	int	number;
}		t_error;

typedef struct		s_state
{
	char		*cmd;
	char		**my_env;
	t_list		*token_list;
	t_ast		*tree;
	t_states	state;
	t_error		error;
	int		file_fd;
	int		status;
	int		easter_egg;
	int		is_debug;
	int		count;
}			t_state;


t_state		*start_machine(int argc, char **argv, char **env);

void    	read_file(t_state **machine);
void		read_input(t_state **machine);
void		expand_input(t_state  **machine);
void		build_state(t_state **machine);
void		execute_tree(t_state **machine);

void		parse_input(t_state **machine);
int		get_token(t_token **token, char *input, int last);
int		check_redir(t_token **token, char *input);
void		reverse_redir(t_list **token_list);
void		first_is_cmd(t_list **token_list);
void		sort_list(t_list **token_list);

t_token		*expand(t_token *token);

void		print_list(t_list *list, int print_type);
char		*get_env_var(char **env, char *var);
char		*get_cmd_path(char *command, char **env);
void		print_tree(t_ast *root, int level);

void		exec_loop(t_ast *root, t_state **machine, t_return **ret, int r_type);
void		exec_redir(t_ast *root, t_ast *r_file, t_return **ret, int type);
void		exec_cmd(t_ast *root, t_state *machine, t_return **ret, int r_type);

int		my_unsetenv(char **argv, t_state **machine);
int		my_env(char **argv, t_state **machine);
int		change_directory(char **argv, t_state **machine);
int		exit_prog(char **argv, t_state **machine);
int		ft_echo(char **argv, t_state **machine);
int		my_set(char **argv, t_state **machine);
int		my_export(char **argv, t_state **machine);

char		**add_new_env(char *new, char **env);
char		**my_unset(char *argv, char **env);
int		env_index(char **env, char *to_find);
char		*get_name(char *str);
char		*get_var(char *str);
void		free_tab(char **tab);
int		my_tablen(char **tab);
char		**my_tabdup(char **tab);
void		print_tab(char **tab);

int		exec_builtin(t_state **machine, t_cmd *cmd);
char		*re_read_input(void);
void		reset(t_state *machine);

char		*extand(char *input, char **env);
void		get_cmd_data(t_ast **root, char **env);
t_token		*create_token(char *input, int type);
int		check_special_char(char c);

void		free_tlist(t_list *list);
void		free_leaf(t_cmd *cmd);
void		free_all(t_state *machine);

void		no_mem_error(void);
void		print_no_found(t_cmd * cmd);
void		print_token_error(char c);
int		check_broke_char(char c);

#endif

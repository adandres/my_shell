/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_shell.h                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 17:12:43 by adandres               /    /  /         */
/*   Updated: 2020/07/11 14:32:54 by adandres                                 */
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
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
int		g_signal;

typedef struct	s_token
{
	int	type;
	void	*content;
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
	int	hdoc;
}		t_redir;

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
	int		l_pid;
}		t_return;

typedef struct	s_ast
{
	int		type;
	void		*data;
	struct s_ast	*left;
	struct s_ast	*right;
}		t_ast;

typedef struct	s_arr
{
	int	x;
	int	y;
}		t_arr;

typedef struct	s_hterm
{
	char	**history;
	char	*cmd;
	char	*save;
	int	pos;
	int	h_len;
	int	curs;
	int	hist;
	int	restart;
	t_arr	win_lim;
	t_arr	curs_pos;
	int	curs_y;
}		t_hterm;

typedef struct		s_state
{
	char		*cmd;
	char		**cmd_tab;
	int		cmd_tab_len;
	int		cmd_tab_i;
	char		**env;
	char		**set;
	char		**history;
	t_list		*token_list;
	t_ast		*tree;
	int		state;
	int		file_fd;
	int		status;
	int		pid;
	int		is_debug;
	int		relaunch;
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
void		first_is_cmd(t_list **token_list, int mode);
void		sort_list(t_list **token_list);
void	assign_word(t_list **token_list);

t_token		*expand(t_token *token);

void		print_list(t_list *list, int print_type);
char		*get_env_var(char **env, char *var);
char		*get_cmd_path(char *command, char **env);
void		print_tree(t_ast *root, int level);

void		exec_loop(t_ast *root, t_state **machine, t_return **ret, int r_type);
int		exec_redir(t_ast *root, t_state *machine,  t_return **ret, int type);
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

int		exec_builtin(t_state **machine, t_cmd *cmd, t_return *ret);
void		re_read_input(t_state **machine);
void		re_read_file(t_state **machine);
void		reset(t_state *machine);

char		*extand(char *input, t_state *machine);
void		get_cmd_data(t_ast **root, t_state *machine);
t_token		*create_token(char *input, int type);
int		check_special_char(char c);

void		free_token(t_token *token);
void		free_tlist(t_list *list);
void		free_leaf(t_cmd *cmd);
void		free_all(t_state *machine);

void		no_mem_error(void);
void		print_no_found(t_cmd * cmd);
void		print_token_error(char c);
int		check_broke_char(char c);

void		write_hdoc(t_state **machine);
char		**my_tab_reverse(char **tab);

void		handle_multiple_command(t_state **machine);
void		print_cmd(t_hterm *hterm, int a);
void		handle_arrows(t_hterm **p_hterm);
int		count_rows(t_hterm *hterm);
void		get_cursor_position(t_hterm *hterm);
void		apply_term(char *op);
void		print_cursor_up(int n);
void		print_cursor_down(int n);
void		print_cursor_left(int n);
void		print_cursor_right(int n);
void		get_cmd(t_hterm **p_hterm);
int		handle_user_input(t_hterm **p_hterm, char c);
void		print_tab_fd(char **tab, int fd);
int		check_quotes(char input, int quoted);
char		**add_or_update_env(char *name, char *var, char **env);
char		**my_tab_add_str(char *src, char **tab, int i);
char		**my_tab_add_str_end(char *src, char **tab);
char		**my_tab_del_str(char **tab, int n);
int		not_a_del(char c);
void		get_terminal_size(t_hterm *hterm);
int		count_lines(t_hterm *hterm, int curs);
void		get_info(t_hterm *hterm);
void		clear_after_cursor(void);
void		place_cursor(int x, int y);
void		place_cursor_at_end(t_hterm *hterm);
void		reset_line(void);
void		erase_line(void);
char		read_after_esc(void);
int		check_sep(char c, char *sep);
int		is_builtin(char *input, int type);
int		my_spe_set(char **argv, t_state **machine);
int		my_setenv(char **argv, t_state **machine);
#endif

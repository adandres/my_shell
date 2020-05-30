/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   starting_state.c                                /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 17:13:38 by adandres               /    /  /         */
/*   Updated: 2020/05/30 14:59:34 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void		check_if_file(t_state **machine, int argc, char **argv)
{
	if (argv[1] && my_strcmp(argv[1], "-debug") == 0 && argc == 2 && isatty(0))
		(*machine)->is_debug = 1;
	else if (argv[1] || isatty(0))
	{
		if (argv[1] == NULL)
			(*machine)->file_fd = 0;
		if (argv[1] && ((*machine)->file_fd = open(argv[1], O_RDONLY)) < 0)
		{
			printf("42sh: %s: No such file or directory\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}
}

static void	my_memtabset(char ***tab, char *set, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		(*tab)[i] = set;
		i++;
	}
}

void	handle_sigusr(int sig)
{
	my_printf("signal: %d\n", sig);
	exit(1);
}

void	handle_sigint(int sig)
{
	(void)sig;
	ioctl(0, TIOCSTI, "\0");
	printf("\n");
}

void	start_signal(void)
{
	signal(SIGUSR1, &handle_sigusr);
	signal(SIGINT, &handle_sigint);
}

char	**my_tab_reverse(char **tab);

char	**read_history(char *filename)
{
	char	*str;
	int	i;
	int	fd;
	char	**history;

	history = (char**)malloc(sizeof(char*) * 256);
	my_memtabset(&history, NULL, 256);
	i = 0;
	fd = open(filename, O_RDONLY | O_CREAT, 0644);
	if (fd < 0)
		printf("shit\n");
	while (get_next_line(fd, &str) > 0 && i < 255)
	{
		if (my_strlen(str) > 0)
		{
			history[i] = str;
			i++;
		}
		else
			free(str);
	}
	close(fd);
	history = my_tab_reverse(history);
	return (history);
}

char			**fill_empty_env(char *name)
{
	char			**env;
	char			*tmp;
	char			dir[1024];
	uid_t			uid;
	struct passwd		*pwd;

	env = NULL;
	getcwd(dir, 1024);
	uid = geteuid();
	pwd = getpwuid(uid);
	tmp = my_strjoin("HOME=/Users/", pwd->pw_name);
	env = add_new_env(tmp, env);
	free(tmp);
	tmp = my_strjoin("LOGNAME=", pwd->pw_name);
	env = add_new_env(tmp, env);
	free(tmp); 
	env = add_new_env("SHLVL=1", env);
	tmp = my_strjoin("PWD=", dir);
	env = add_new_env(tmp , env);
	free(tmp);
	//env = my_setenv("OLDPWD", dir, env);
	tmp = my_strjoin("_=", name);
	env = add_new_env(tmp , env);
	free(tmp);
	return (env);
}

char			**add_shlvl(char **env)
{
	int			i;
	int			nb;
	char		*var;

	if (!env)
		return (NULL);
	i = env_index(env, "SHLVL");
	if (i < 0)
		return (NULL);
	else
	{
		var = get_var(env[i]);
		nb = my_atoi(var);
		nb++;
		free(env[i]);
		free(var);
		var = my_itoa(nb);
		env[i] = my_strjoin("SHLVL=", var);
		free(var);
	}
	return (env);
}

char			**copy_check_env(char *name, char **env, int a)
{
	char		**new_env;
	char		*tmp;

	new_env = NULL;
	if (env && env[0])
		new_env = my_tabdup(env);
	else
		new_env = fill_empty_env(name);
	new_env = add_shlvl(new_env);
	tmp = my_strjoin("_=", name);
	new_env = add_new_env(tmp, new_env);
	free(tmp);
	return (new_env);
}

t_state	*start_machine(int argc, char **argv, char **env)
{
	t_state		*machine;

	if (!(machine = (t_state*)malloc(sizeof(t_state))))
		no_mem_error();
	machine->file_fd = -1;
	machine->status = 0;
	machine->is_debug = 0;
	machine->cmd_tab = NULL;
	machine->cmd_tab_len = 0;
	machine->cmd_tab_i = 0;
	machine->tree = NULL;
	machine->cmd = NULL;
	machine->history = NULL;
	machine->my_env = NULL;
	machine->token_list = NULL;
	if (argc != 0)
	machine->my_env = copy_check_env(argv[0], env, argc);
	if (argc != 0)
		machine->history = read_history(".my_shell_history");
	if (argc > 1)
		check_if_file(&machine, argc, argv);
	if (isatty(1) && argc != 0)
		apply_term("INIT");
	if (argc != 0)
		start_signal();
	machine->state = READ;
	return (machine);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_env.c                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/08 01:32:33 by adandres               /    /  /         */
/*   Updated: 2020/06/04 14:53:31 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void		free_state(t_state *machine);
void		free_this(t_list *list);
int		relaunch(char **argv, char **cpy);


static int check_option(char *input)
{
	int	i;

	i = 1;
	while (input[i])
	{
		if (input[i] == 'u')
			return (i);
		if (input[i] != 'i')
		{
			printf("illegal option -- %c\n", input[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static int		check_unset(char **argv, int j, char ***pcpy)
{
	char	**cpy;
	int	i;
	
	i = 0;
	cpy = *pcpy;
	if (argv[i][j] == 'u')
	{
		if (argv[i][j + 1] != '\0')
			cpy = my_unset(argv[i] + j + 1, cpy);
		else
			cpy = my_unset(argv[++i], cpy);
	}
	*pcpy = cpy;
	return (i);
}

static int		check_set(char **argv, char ***pcpy)
{
	int	i;
	char	**cpy;

	i = 0;
	cpy = *pcpy;
	if (argv == NULL)
		return (i);
	while (argv[i] && my_strichr(argv[i], '=') >= 0)
	{
		cpy = add_new_env(argv[i], cpy);
		i++;
	}
	*pcpy = cpy;
	return (i);
}

static void		free_cpy(char ***cpy, char ***pcpy)
{
	if (*cpy)
		free_tab(*cpy);
	*cpy = NULL;
	pcpy = cpy;
}

static int		parse_options(char **argv, char ***pcpy)
{
	char		**cpy;
	int		i;
	int		j;

	i = 1;
	cpy = *pcpy;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 1;
		if (argv[i][1] == 'i')
		{
			free_cpy(&cpy, pcpy);
			if ((j = check_option(argv[i])) == 0)
				return (1);
		}
		i += check_unset(argv + i, j, &cpy);
		i++;
	}
	i += check_set(argv + i, &cpy);
	*pcpy = cpy;
	if (argv[i] != NULL && argv)
		return (i);
	return (0);
}

int				my_env(char **argv, t_state **machine)
{
	char	**cpy;
	char	*command;
	int	index;
	int	status;

	status = 0;
	cpy = my_tabdup((*machine)->my_env);
	if ((index = parse_options(argv, &cpy)) == 0 && cpy)
		print_tab(cpy);
	if (index > 0)
	{
		command = argv[index];
		argv[index] = get_cmd_path(command, (*machine)->my_env);
		free(command);
		relaunch(argv + index, cpy);
	}
	else
		status = 1;
	if (cpy)
		free_tab(cpy);
	return (status);
}

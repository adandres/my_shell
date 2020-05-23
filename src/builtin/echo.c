/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   echo.c                                          /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/08 21:56:22 by adandres               /    /  /         */
/*   Updated: 2020/05/23 19:07:02 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char **my_tab_reverse(char **tab);

int		exit_prog(char **argv, t_state **machine)
{
	int		i;
	int		fd;

	i = 0;
	while (argv && argv[i])
		i++;
	if (i > 2)
	{
		my_putendl("Error: too many arguments");
		return (1);
	}
	(*machine)->state = END;
	/*fd = open(".my_shell_history", O_WRONLY, O_APPEND);
	(*machine)->history = my_tab_reverse((*machine)->history);
	print_tab_fd((*machine)->history, fd);
	close(fd);
	free_all(*machine);
	*machine = NULL;
	exit(127);*/
	return (0);
}

int		ft_echo(char **argv, t_state **machine)
{
	int		i;
	int		a;

	i = 1;
	a = 0;
	while (argv && argv[i] && argv[i][0] == '-')
	{
		if (my_strichr(argv[i], 'n') == -1)
			break;
		a = 1;
		i++;
	}
	while (argv[i])
	{
		my_putstr(argv[i]);
		if (argv[i + 1] && argv[i + 1][0])
			my_putchar(' ');
		i++;
	}
	if (a == 0)
		my_putchar('\n');
	(*machine)->status = 0;
	return (0);
}

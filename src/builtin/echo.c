/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   echo.c                                          /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/08 21:56:22 by adandres               /    /  /         */
/*   Updated: 2020/04/18 18:28:29 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		exit_prog(char **argv, t_state **machine)
{
	int		i;

	i = 1;
	while (argv[i])
		i++;
	if (i > 2)
	{
		my_putendl("Error: too many arguments");
		return (1);
	}
	argv = NULL;
	free_all(*machine);
	exit(127);
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
		if (argv[i + 1])
			my_putchar(' ');
		i++;
	}
	if (a == 0)
		my_putchar('\n');
	(*machine)->status = 0;
	return (0);
}

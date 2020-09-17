/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_setenv.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/07/03 07:41:34 by adandres               /    /  /         */
/*   Updated: 2020/07/03 07:42:43 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		my_setenv(char **argv, t_state **machine)
{
	int     i;

	i = 0;
	while (argv[i])
	{
		if (my_strichr(argv[i], '=') > 0)
			(*machine)->env = add_new_env(argv[i], (*machine)->env);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_export.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/16 16:47:44 by adandres               /    /  /         */
/*   Updated: 2020/06/21 13:21:12 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int     my_export(char **argv, t_state **machine)
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

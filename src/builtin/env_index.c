/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   env_index.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/08 17:15:54 by adandres               /    /  /         */
/*   Updated: 2020/06/22 12:58:03 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	env_index(char **env, char *to_find)
{
	int	i;
	int	len;

	i = 0;
	if (env == NULL)
		return (-1);
	len = my_strlen(to_find);
	while (env[i])
	{
		if (my_strncmp(env[i], to_find, my_strichr(env[i], '=')) == 0)
			return (i); 
		i++;
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_export.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/16 16:47:44 by adandres               /    /  /         */
/*   Updated: 2020/07/03 15:23:22 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static char *look_for_var(char *str, char **tab)
{
	int	i;
	char	*to_find;
	char	*name;

	i = 0;
	to_find = get_name(str);
	while (tab[i])
	{
		name = get_name(tab[i]);
		if (my_strcmp(to_find, name) == 0)
		{
			free(name);
			free(to_find);
			return (my_strdup(tab[i]));
		}
		free(name);
		i++;
	}
	free(to_find);
	return (NULL);
}

int     my_export(char **argv, t_state **machine)
{
	int     i;
	char	*new;

	i = 1;
	new = NULL;
	while (argv[i])
	{
		if (my_strichr(argv[i], '=') > 0)
			(*machine)->env = add_new_env(argv[i], (*machine)->env);
		if ((new = look_for_var(argv[i], (*machine)->set)) != NULL)
			(*machine)->env = add_new_env(new, (*machine)->env);
		i++;
	}
	return (0);
}

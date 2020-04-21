/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   tab.c                                           /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/08 22:07:02 by adandres               /    /  /         */
/*   Updated: 2020/04/20 20:47:13 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void		free_tab(char **tab)
{
	int i;
	
	i = 0;
	if (tab == NULL)
		return;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		my_tablen(char **tab)
{
	int		i;
	
	i = 0;
	if (tab == NULL)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i);
}

char				**my_tabdup(char **tab)
{
	char		**cpy;
	int		i;
	int		len;

	i = 0;
	len = my_tablen(tab);
	if (!(cpy = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	while (tab[i] != NULL)
	{
		if ((cpy[i] = my_strdup(tab[i])) == NULL)
			return (NULL);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void				print_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		my_putendl(tab[i++]);
}

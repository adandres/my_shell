/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   tab.c                                           /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/08 22:07:02 by adandres               /    /  /         */
/*   Updated: 2020/06/04 14:51:33 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

char	**my_tab_del_str(char **tab, int n)
{
	int	i;
	int	j;
	char	**new_tab;

	i = 0;
	j = 0;
	new_tab = (char **)malloc(sizeof(char*) * my_tablen(tab));
	while (tab[i])
	{
		if (i != n)
		{
			new_tab[j] = tab[i];
			j++;
		}
		else
			free(tab[i]);
		i++;
	}
	new_tab[j] = NULL;
	free(tab);
	return (new_tab);
}

char	**my_tab_add_str(char *src, char **tab, int n)
{
	int	i;
	int	j;
	char	**new_tab;

	i = 0;
	j = 0;
	new_tab = (char **)malloc(sizeof(char*) * (my_tablen(tab) + 2));
	if (tab[0] == NULL)
	{
		new_tab[0] = my_strdup(src);
		new_tab[1] = NULL;
		free(tab);
		return (new_tab);
	}
	while (tab[i] && i < n)
	{
		new_tab[j] = tab[i];
		i++;
		j++;
	}
	new_tab[j] = my_strdup(src);
	j++;
	while (tab[i])
	{
		new_tab[j] = tab[i];
		i++;
		j++;
	}
	new_tab[j] = NULL;
	free(tab);
	return (new_tab);
}

char	**my_tab_add_str_end(char *src, char **tab)
{
	int	i;
	int	j;
	char	**new_tab;

	i = 0;
	j = 0;
	new_tab = (char **)malloc(sizeof(char*) * (my_tablen(tab) + 2));
	while (tab && tab[i])
	{
		new_tab[j] = tab[i];
		i++;
		j++;
	}
	new_tab[j] = my_strdup(src);
	new_tab[j + 1] = NULL;
	free(tab);
	return (new_tab);
}

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

void				print_tab_fd(char **tab, int fd)
{
	int		i;

	i = 0;
	while (tab[i])
		my_putendl_fd(tab[i++], fd);
}

void			print_tab(char **tab)
{
	print_tab_fd(tab, 1);
}

char		**my_tab_reverse(char **tab)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	j = my_tablen(tab) - 1;
	while (i < j && i != j)
	{
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
		i++;
		j--;
	}
	return (tab);
}

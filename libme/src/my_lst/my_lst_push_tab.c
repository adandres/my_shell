/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_lst_push_tab.c                               /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/17 14:48:22 by adandres               /    /  /         */
/*   Updated: 2020/03/22 15:06:27 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

t_list		*my_lst_push_tab(char **av)
{
	t_list		*list;
	int			i;

	i = 1;
	if (!av)
		return (NULL);
	list = my_lst_new(av[0], my_strlen(av[0]));
	while (av[i])
	{
		list = my_lst_add(list, av[i], my_strlen(av[i]));
		i++;
	}
	return (list);
}

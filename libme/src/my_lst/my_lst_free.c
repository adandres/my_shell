/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_lst_free.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 02:14:06 by adandres               /    /  /         */
/*   Updated: 2020/04/19 02:18:43 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_lst.h"

void	my_lst_free(t_list *list)
{
	t_list *next;

	while (list)
	{
		next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
}

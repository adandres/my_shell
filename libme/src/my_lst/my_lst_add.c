/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_lst_add.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/17 14:52:16 by adandres               /    /  /         */
/*   Updated: 2020/03/22 15:06:17 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

t_list	*ft_lst_add(t_list *list, void *content, size_t content_size)
{
	t_list *tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp)
	{
		if (!(tmp->content = malloc(content_size)))
			return (0);
		tmp->content = content;
		tmp->content_size = content_size;
		tmp->next = list;
	}
	return (tmp);
}

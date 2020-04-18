/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_lst.h                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/17 14:53:16 by adandres               /    /  /         */
/*   Updated: 2020/04/18 19:42:26 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_LST_H
# define MY_LST_H

#include <stdlib.h>

typedef struct	s_list
{
	void		*content;
	size_t		content_size;
	struct s_list	*next;
}		t_list;

t_list		*my_lst_add(t_list *list, void *content, size_t content_size);
t_list		*my_lst_new(void const *content, size_t content_size);
t_list		*my_lst_push_tab(char **av);
void		my_lst_reverse(t_list **begin_list);
int		my_lst_len(t_list *list);
t_list		*my_lst_pass(t_list *list, int n);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strcdel.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 02:03:52 by adandres               /    /  /         */
/*   Updated: 2020/04/19 02:05:02 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

char		*my_strcdel(char *str, int i)
{
	char	*head;

	head = my_strndup(str, i);
	if (str[i + 1])
		head = my_strjoin_free(head, str + i + 1);
	free(str);
	return (head);
}

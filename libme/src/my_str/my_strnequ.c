/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strnequ.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 19:01:08 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:19:35 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

int		my_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (my_strncmp(s1, s2, n) == 0)
		return (1);
	else
		return (0);
}

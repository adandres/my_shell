/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strnstr.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 19:02:29 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:20:06 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

char	*my_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t find;
	size_t e;
	size_t a;

	i = 0;
	find = 0;
	while (to_find[find++])
		;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		e = 0;
		a = i;
		while (str[a++] == to_find[e++] && e <= find && a <= len)
		{
			if (e == find - 1)
				return ((char *)str + a - e);
		}
		i++;
	}
	return (0);
}

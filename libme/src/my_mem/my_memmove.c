/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_memmove.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 17:53:44 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:54:40 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_mem.h"

void	*my_memmove(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (s < d)
	{
		while (n--)
			d[n] = s[n];
	}
	else
		my_memcpy(d, s, n);
	return (d);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_memccpy.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 17:46:20 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:54:00 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_mem.h"

void		*my_memccpy(void *dst, const void *src, int c, size_t size)
{
	size_t		i;
	unsigned char	*source;
	unsigned char	*desti;

	i = 0;
	source = (unsigned char *)src;
	desti = (unsigned char *)dst;
	while (i < size)
	{
		desti[i] = source[i];
		if (source[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}

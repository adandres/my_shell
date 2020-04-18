/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_memset.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 17:54:49 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:54:49 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_mem.h"

void	*my_memset(void *b, int c, size_t len)
{
	unsigned char *cur;

	if (len == 0)
		return (b);
	cur = (unsigned char *)b;
	while (len--)
	{
		*cur = (unsigned char)c;
		if (len)
			cur++;
	}
	return (b);
}

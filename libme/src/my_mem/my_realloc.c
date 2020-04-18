/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_realloc.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 17:52:52 by adandres               /    /  /         */
/*   Updated: 2020/04/18 19:00:03 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_mem.h"

#include <stdlib.h>
#include <stdio.h>


void	*my_realloc(void *src, size_t src_size, size_t final_size)
{
	void	*ret;

	ret = NULL;
	if (src && src_size < final_size)
	{
		ret = my_memalloc(final_size);
		if (ret)
			my_memcpy(ret, src, src_size);
	}
	free(src);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_memalloc.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 17:45:10 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:53:43 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_mem.h"

void		*my_memalloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (mem == NULL)
		return (NULL);
	my_bzero(mem, size);
	return (mem);
}

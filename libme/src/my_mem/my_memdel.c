/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_memdel.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 17:53:06 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:54:33 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_mem.h"

void	my_memdel(void **ap)
{
	free(*ap);
	*ap = NULL;
}

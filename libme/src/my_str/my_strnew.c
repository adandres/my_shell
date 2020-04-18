/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strnew.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 19:01:38 by adandres               /    /  /         */
/*   Updated: 2020/03/22 15:06:01 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

char	*my_strnew(size_t size)
{
	char *str;

	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	my_bzero(str, size);
	return (str);
}

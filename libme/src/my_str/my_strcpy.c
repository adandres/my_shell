/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strcpy.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 18:54:11 by adandres               /    /  /         */
/*   Updated: 2020/05/23 00:40:49 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

char	*my_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	my_bzero(dest, my_strlen(dest));
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

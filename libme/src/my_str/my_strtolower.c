/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strtolower.c                                 /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/02 16:26:14 by adandres               /    /  /         */
/*   Updated: 2020/04/02 16:28:03 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

char		*my_strtolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = my_tolower(str[i]);
		i++;
	}
	return (str);
}
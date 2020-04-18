/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strtoupper.c                                 /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/02 16:16:59 by adandres               /    /  /         */
/*   Updated: 2020/04/02 16:25:54 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

char	*my_strtoupper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = my_toupper(str[i]);
		i++;
	}
	return (str);
}

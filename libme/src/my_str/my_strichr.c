/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strichr.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:22:41 by adandres               /    /  /         */
/*   Updated: 2020/04/18 19:28:07 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

int		my_strichr(char *str, char to_find)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == to_find)
			break;
		i++;
	}
	if (str[i])
		return (i);
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strnchr.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/31 15:42:00 by adandres               /    /  /         */
/*   Updated: 2020/05/31 15:46:10 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

int	my_strnchr(char *str, int n, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && i < n)
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_striteri.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 18:56:42 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:17:44 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int i;

	i = 0;
	if (s != NULL && f != NULL)
	{
		while (*s != '\0')
		{
			f(i, s);
			i++;
			s++;
		}
	}
}

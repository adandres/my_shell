/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strmap.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 18:58:40 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:18:41 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

char	*my_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (s && f)
	{
		str = my_strnew(my_strlen(s));
		if (str == NULL)
			return (NULL);
		while (s[i])
		{
			str[i] = f(s[i]);
			i++;
		}
		return (str);
	}
	return (NULL);
}

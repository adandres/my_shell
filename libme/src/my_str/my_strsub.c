/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strsub.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 19:06:30 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:21:05 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

char	*my_strsub(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*str;

	i = 0;
	str = NULL;
	if (s == NULL)
		return (str);
	while (i < len)
	{
		if (!s[i])
			return (NULL);
		i++;
	}
	if ((str = (char *)malloc(sizeof(*str) * len + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

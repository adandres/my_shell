/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strjoin.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 18:56:55 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:18:07 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

char	*my_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = my_strlen(s1) + my_strlen(s2);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (str == NULL)
		return (NULL);
	my_strcpy(str, s1);
	my_strcat(str, s2);
	return (str);
}

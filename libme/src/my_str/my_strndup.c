/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strndup.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 19:53:02 by adandres               /    /  /         */
/*   Updated: 2020/04/06 19:53:49 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

char	*my_strndup(const char *s1, int len)
{
	int		i;
	char	*s2;

	i = 0;
	if (!(s2 = (char *)malloc(sizeof(*s2) * (len + 1))))
		return (NULL);
	while (s1[i] && len)
	{
		s2[i] = s1[i];
		i++;
		len--;
	}
	s2[i] = '\0';
	return (s2);
}

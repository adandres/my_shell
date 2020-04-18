/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strrchr.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 19:03:05 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:20:18 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = my_strlen(s);
	while (len != 0 && s[len] != (char)c)
		len--;
	if (s[len] == (char)c)
		return ((char *)&s[len]);
	return (NULL);
}

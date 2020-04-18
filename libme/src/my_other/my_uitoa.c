/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_uitoa.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/02 15:44:15 by adandres               /    /  /         */
/*   Updated: 2020/04/02 15:53:50 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_other.h"

char		*my_uitoa(uintmax_t n)
{
	uintmax_t		tmpn;
	int			len;
	char			*str;

	tmpn = n;
	len = 0;
	while (tmpn /= 10)
		len++;
	if ((str = (char *)malloc(sizeof(*str) * (len + 1))) == NULL)
		return (NULL);
	str[len + 1] = '\0';
	while (len >= 0)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_uitoa_base.c                                 /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/29 00:43:27 by adandres               /    /  /         */
/*   Updated: 2020/04/02 15:42:40 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

char	*my_uitoa_base(uintmax_t nbr, char *base)
{
	uintmax_t	temp;
	uintmax_t	len;
	char		*str;
	int		i;

	temp = nbr;
	len = 0;
	i = 0;
	while (base[len])
		len++;
	while (temp >= len)
	{
		temp = temp / len;
		i++;
	}
	str = (char*)malloc(sizeof(char) * (i + 1));
	str[i + 1] = '\0';
	while (i >= 0)
	{
		temp = nbr % len;
		str[i] = base[temp];
		nbr = nbr / len;
		i--;
	}
	return (str);
}

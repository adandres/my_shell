/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_itoa.c                                       /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/22 14:41:06 by adandres               /    /  /         */
/*   Updated: 2020/04/02 15:40:28 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

static void		is_negative(intmax_t *n, int *neg)
{
	if (*n < 0)
	{
		*n *= -1;
		*neg = 1;
	}
}

char			*my_itoa(intmax_t n)
{
	intmax_t	tmpn;
	int		len;
	int		neg;
	char		*str;

	neg = 0;
	tmpn = n;
	len = 0;
	is_negative(&n, &neg);
	if (n == -2147483648)
		return (my_strdup("-2147483648"));
	while (tmpn /= 10)
		len++;
	len += neg;
	if ((str = (char *)malloc(sizeof(*str) * (len + 1))) == NULL)
		return (NULL);
	str[len + 1] = '\0';
	while (len >= 0)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	if (neg)
		str[0] = '-';
	return (str);
}

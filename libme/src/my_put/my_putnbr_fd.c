/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_putnbr_fd.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 11:42:29 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:55:52 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_put.h"

void		my_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		my_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			my_putchar_fd('-', fd);
			n = -n;
		}
		if (n >= 10)
			my_putnbr_fd(n / 10, fd);
		my_putchar_fd((n % 10) + '0', fd);
	}
}

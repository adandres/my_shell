/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_printf.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/18 11:54:15 by adandres               /    /  /         */
/*   Updated: 2020/03/31 15:00:34 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

int	my_printf(const char * restrict format, ...)
{
	va_list ap;
	int	i;
	int	f_len;

	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if ((f_len = print_format(format + i + 1, ap)) > 0)
				i += f_len;
			else
				my_putchar(format[i]);
			i++;
		}
		else
			my_putchar(format[i++]);
	}
	va_end(ap);
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   print_cursor.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:52:06 by adandres               /    /  /         */
/*   Updated: 2020/05/26 23:53:47 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void		print_cursor_up(int n)
{
	my_printf("\x1b[%dA", n);
}

void		print_cursor_down(int n)
{
	my_printf("\x1b[%dB", n);
}

void		print_cursor_right(int n)
{
	my_printf("\x1b[%dC", n);
}

void		print_cursor_left(int n)
{
	my_printf("\x1b[%dD", n);
}

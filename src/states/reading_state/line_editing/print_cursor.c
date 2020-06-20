/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   print_cursor.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:52:06 by adandres               /    /  /         */
/*   Updated: 2020/06/20 17:31:29 by adandres                                 */
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

void		clear_after_cursor(void)
{
	my_printf("\x1b[K");
	my_printf("\x1b[J");
}

void		place_cursor_at_end(t_hterm *hterm)
{
	int a;

	if (hterm->curs == 0)
		return;
	a = count_lines(hterm, hterm->pos - hterm->curs);
	print_cursor_down(a + 2);
}

void		place_cursor(int y, int x)
{
	my_printf("\x1b[%d;%df", y, x);
}

void		erase_line(void)
{
	my_printf("\x1b[2K");
}

void		reset_line(void)
{
	erase_line();
	print_cursor_left(3);
}

char		read_after_esc(void)
{
	char	c;

	read(0, &c, 1);
	read(0, &c, 1);
	return (c);
}

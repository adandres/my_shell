/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cursor_position.c                           /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:29:43 by adandres               /    /  /         */
/*   Updated: 2020/06/20 17:09:09 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void		get_terminal_size(t_hterm *hterm)
{
	struct ttysize	ts;
	ioctl(0, TIOCGSIZE, &ts);
	hterm->win_lim.x = ts.ts_cols;
	hterm->win_lim.y = ts.ts_lines;
}

int		read_number(char c)
{
	int	nb;

	nb = 0;
	while (c >= '0' && c <= '9')
	{
		nb = nb * 10 + c - '0';
		read(0, &c, 1);
	}
	return (nb);
}

void		get_cursor_position(t_hterm *hterm)
{
	char	c;

	c = 0;
	write(1, "\x1b[6n", 4);
	while (c != ESC)
		read(0, &c, 1);
	if (c != ESC)
	{
		my_printf("error: %c\n", c);
		exit(1);
	}
	c = read_after_esc();
	hterm->curs_pos.y = read_number(c);
	read(0, &c, 1);
	hterm->curs_pos.x = read_number(c);
}

void		get_info(t_hterm *hterm)
{
	get_cursor_position(hterm);
	get_terminal_size(hterm);
	hterm->n_lines = count_lines(hterm, 0);
}

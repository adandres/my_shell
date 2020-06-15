/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cursor_position.c                           /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:29:43 by adandres               /    /  /         */
/*   Updated: 2020/06/15 20:09:07 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void		get_terminal_size(t_hterm **p_hterm)
{
	struct ttysize	ts;
	ioctl(0, TIOCGSIZE, &ts);
	(*p_hterm)->win_lim.x = ts.ts_cols;
	(*p_hterm)->win_lim.y = ts.ts_lines;
}

void		get_input_info(t_hterm **p_hterm)
{
	(*p_hterm)->n_lines = count_lines((*p_hterm)->cmd, (*p_hterm)->win_lim.x, 0 ,0);
}

void		get_cursor_position(t_hterm **p_hterm)
{
	int	row;
	int	col;
	char	c;

	row = 0;
	col = 0;
	c = 0;
	write(1, "\x1b[6n", 4);
	while (c != ESC)
		read(0, &c, 1);
	if (c != ESC)
	{
		my_printf("error: %c\n", c);
		exit(1);
	}
	read(0, &c, 1);
	read(0, &c, 1);
	while (c >= '0' && c <= '9')
	{
		row = row * 10 + c - '0';
		read(0, &c, 1);
	}
	read(0, &c, 1);
	while (c >= '0' && c <= '9')
	{
		col = col * 10 + c - '0';
		read(0, &c, 1);
	}
	(*p_hterm)->curs_pos.y = row;
	(*p_hterm)->curs_pos.x = col;
}

void		get_info(t_hterm **p_hterm)
{
	get_cursor_position(p_hterm);
	get_terminal_size(p_hterm);
	get_input_info(p_hterm);
}

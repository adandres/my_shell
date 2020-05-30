/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cursor_position.c                           /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:29:43 by adandres               /    /  /         */
/*   Updated: 2020/05/30 19:35:51 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void		get_cursor_position(t_hterm **p_hterm)
{
	int	row;
	int	col;
	char	c;
	struct termios term, restore;

 	tcgetattr(0, &term);
 	tcgetattr(0, &restore);
	tcsetattr(0, TCSANOW, &term);
	row = 0;
	col = 0;
	c = 0;
	my_printf("\x1b[6n");
	while (c != ESC)
		read(0, &c, 1);
	if (c != ESC)
	{
		tcsetattr(0, TCSANOW, &restore);
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
	(*p_hterm)->row = row;
	(*p_hterm)->col = col;
	tcsetattr(0, TCSANOW, &restore);
}

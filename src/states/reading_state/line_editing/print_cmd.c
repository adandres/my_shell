/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   print_cmd.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:08:55 by adandres               /    /  /         */
/*   Updated: 2020/06/20 19:23:05 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void		spe_print(t_hterm *hterm, int n_lines)
{
	int	i;
	int	x;
	char	*str;

	i = 0;
	str = hterm->cmd;
	x = 3;
	while (str[i])
	{
		if (x == hterm->win_lim.x + 1 && str[i] == '\n')
		{
			printf("\n");
		if (n_lines + hterm->curs_pos.y == hterm->win_lim.y)
			hterm->curs_pos.y -= 1;
			x = 0;
		}
		if (str[i] == '\n')
			x = 0;
		if (x == hterm->win_lim.x && str[i + 1] != '\n')
			x = 0;
		my_putchar(str[i]);
		x++;
		i++;
	}
	if (x == hterm->win_lim.x)
		my_printf("\n");
}

void		print_cmd(t_hterm *hterm, int a)
{
	int	n_lines;

	n_lines = 0;
	place_cursor(hterm->curs_pos.y - hterm->curs_y, 4);
	clear_after_cursor();
	n_lines = count_lines(hterm, hterm->pos - hterm->curs);
	spe_print(hterm, n_lines);
	if (hterm->curs)
	{
		if (n_lines + hterm->curs_pos.y > hterm->win_lim.y)
			hterm->curs_pos.y -= 1;
		if ((hterm->win_lim.x == hterm->curs_pos.x && a == 1))
		{
			if (n_lines + hterm->curs_pos.y <= hterm->win_lim.y)
				hterm->curs_pos.y += 1;
			hterm->curs_y += 1;
			hterm->curs_pos.x = 0;
		}
	}
	else if (hterm->win_lim.x == hterm->curs_pos.x && a == 1)
	{
		if (hterm->curs_pos.y != hterm->win_lim.y)
			hterm->curs_pos.y += 1;
		hterm->curs_y += 1;
		hterm->curs_pos.x = 0;
	}
	place_cursor(hterm->curs_pos.y, hterm->curs_pos.x + a);
}

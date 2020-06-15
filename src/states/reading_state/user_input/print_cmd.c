/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   print_cmd.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:08:55 by adandres               /    /  /         */
/*   Updated: 2020/06/15 20:22:54 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void		lala(t_hterm *hterm, int a)
{
	my_printf("\033D");
	my_printf("\x1b[%d;%df", hterm->curs_pos.y - 1, hterm->curs_pos.x + a);
	my_printf("\x1b[K");
	my_printf("\x1b[J");
	my_printf("%s", hterm->cmd + (hterm->pos - hterm->curs + 1));
	my_printf("\x1b[%d;%df", hterm->curs_pos.y, 1);
	my_printf("\x1b[K");
	my_printf("\x1b[J");
	my_printf("%s", hterm->cmd + (hterm->pos - hterm->curs + (hterm->win_lim.x - hterm->curs_pos.x) + 1));
	my_printf("\x1b[%d;%df", hterm->curs_pos.y - 1, hterm->curs_pos.x + a);
}

void		lolo(t_hterm *hterm, int a)
{
	my_printf("\x1b[%d;%df", hterm->curs_pos.y, hterm->curs_pos.x + a);
	my_printf("\x1b[K");
	my_printf("\x1b[J");
	my_printf("%s", hterm->cmd + (hterm->pos - hterm->curs + 1));
	my_printf("\x1b[%d;%df", hterm->curs_pos.y + 1, 1);
	my_printf("\x1b[K");
	my_printf("\x1b[J");
	my_printf("%s", hterm->cmd + (hterm->pos - hterm->curs + (hterm->win_lim.x - hterm->curs_pos.x) + 1));
	my_printf("\x1b[%d;%df", hterm->curs_pos.y, hterm->curs_pos.x + a);

}

void		print_cmd(t_hterm *hterm, int a)
{
	int	n_lines;
	int	nnn;
	int	b;

	b = 0;
	n_lines = 0;
	if (hterm->curs)
	{
		my_printf("\x1b[K");
		my_printf("\x1b[J");
	}
	my_printf("%s", hterm->cmd + (hterm->pos - hterm->curs));
	if (hterm->curs)
	{
		n_lines = count_lines(hterm->cmd, hterm->win_lim.x, hterm->pos - hterm->curs, 0);
		nnn = count_lines(hterm->cmd, hterm->win_lim.x, 0, 0);
		if ((hterm->win_lim.x == hterm->curs_pos.x && a == 1))
		{	
			my_printf("\x1b[%d;%df", hterm->curs_pos.y + a, 1);
			my_printf("\x1b[K");
			my_printf("\x1b[J");
			my_printf("%s", hterm->cmd + (hterm->pos - hterm->curs + 1));
			if (hterm->cmd[hterm->pos - hterm->curs + 1] == '\n' && n_lines + hterm->curs_pos.y == hterm->win_lim.y)
				a = 0;
			my_printf("\x1b[%d;%df", hterm->curs_pos.y + a, 1);
		}
		else if (nnn > hterm->n_lines)
		{
			if (n_lines + hterm->curs_pos.y > hterm->win_lim.y)
				lala(hterm, a);
			else
				lolo(hterm, a);
		}
		else
			my_printf("\x1b[%d;%df", hterm->curs_pos.y, hterm->curs_pos.x + a);

	}
	else if (hterm->win_lim.x == hterm->curs_pos.x && a == 1)
	{
		if (hterm->curs_pos.y == hterm->win_lim.y)
			my_printf("\033D");
		my_printf("\x1b[%d;%df", hterm->curs_pos.y + a, 1);
	}
}

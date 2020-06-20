/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   count.c                                         /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:26:29 by adandres               /    /  /         */
/*   Updated: 2020/06/20 19:38:11 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	count_lines(t_hterm *hterm, int curs)
{
	int	ligne;
	int	x;
	int	i;

	i = 0;
	ligne = 0;
	x = 2;
	while (hterm->cmd[i])
	{
		x++;
		if (hterm->cmd[i] == '\n')
		{
			ligne++;
			x = 0;
		}
		if (x == hterm->win_lim.x)
		{
			ligne++;
			x = 0;
		}
		if (i == curs && curs != 0)
			ligne = 0;
		i++;
	}
	if (x + 1 == hterm->win_lim.x)
		ligne++;
	return (ligne);
}

int	count_rows(t_hterm *hterm)
{
	int	ligne;
	int	x;
	int	n;
	int	i;

	ligne = 1;
	x = 2;
	i = 0;
	n = hterm->pos - hterm->curs;
	while (hterm->cmd[i] && i < n - 1)
	{
		x++;
		if (hterm->cmd[i] == '\n')
		{
			x = 0;
			ligne++;
		}
		if (x % (hterm->win_lim.x) == 0 && x != 0)
			x = 0;
		i++;
	}
	if (ligne == 1)
		x += 3;
	return (x);
}

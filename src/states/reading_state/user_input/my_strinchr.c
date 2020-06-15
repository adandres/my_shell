/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strinchr.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:26:29 by adandres               /    /  /         */
/*   Updated: 2020/06/15 21:08:16 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	count_lines(char *str, int width, int curs, int n_ligne)
{
	int	count;
	int	i;
	int	li;

	i = 0;
	count = 0;
	li = 2;
	while (str[i])
	{
		li++;
		if (str[i] == '\n' && li != 0)
		{
			count++;
			li = 0;
		}
		else if (li % (width) == 0 && i != 0 && li != 0)
		{
			count++;
			li = 0;
		}
		if (i == curs && curs != 0)
			count = 0;
		i++;
	}
	return (count);
}

int	my_strinchr(char *str, int n, int width)
{
	int	nb;
	int	re;
	int	i;

	nb = 0;
	i = 0;
	re = 0;
	while (str[i] && i < n - 1)
	{
		nb++;
		if (str[i] == '\n')
		{
			nb = 0;
			re++;
		}
		if (nb % (width) == 0 && i != 0 && nb != 0)
			nb = 0;
		i++;
	}
	if (re == 0)
		nb += 3;
	return (nb);
}

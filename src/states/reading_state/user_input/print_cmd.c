/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   print_cmd.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:08:55 by adandres               /    /  /         */
/*   Updated: 2020/05/30 19:04:46 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void		print_cmd(t_hterm *hterm, int a)
{
	if (hterm->curs)
	{
		get_cursor_position(&hterm);
		my_printf("\x1b[K");
	}
	my_printf("%s", hterm->cmd + hterm->pos - hterm->curs - 1);
	if (hterm->curs)
		my_printf("\x1b[%d;%df", hterm->row, hterm->col + a);
}

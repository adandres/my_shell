/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   handle_user_input.c                             /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:02:03 by adandres               /    /  /         */
/*   Updated: 2020/06/20 19:38:50 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static char	del_inline(t_hterm *hterm)
{
	int	i;
	char	tmp;
	char	prev;

	i = hterm->pos;
	prev = 0;
	while (i >= 0)
	{
		tmp = hterm->cmd[i];
		hterm->cmd[i] = prev;
		if (i < hterm->pos - hterm->curs)
			break;
		prev = tmp;
		i--;
	}
	return (tmp);
}

static void	del_prev_char(t_hterm *hterm)
{
	char	del;
	int	a;

	a = 0;
	if (hterm->curs == hterm->pos)
		return;
	del = del_inline(hterm);
	if (del == '\n' || hterm->curs_pos.x == 1)
	{
		my_printf("\x1b[J");
		my_printf(ARROW_UP);
		a = count_rows(hterm);
		if (a > 0)
			print_cursor_right(a);
		get_cursor_position(hterm);
		if (a > 0)
			hterm->curs_pos.x++;
		hterm->curs_y -= 1;
	}
	else
		my_printf(DEL_PREV_CHAR);
	hterm->pos -= 1;
	if (hterm->curs)
		print_cmd(hterm, -1);
}

static void		reset_cmd(t_hterm *hterm)
{
	my_bzero(hterm->cmd, my_strlen(hterm->cmd));
	hterm->pos = 0;
	hterm->curs = 0;
	hterm->restart = 1;
}

int		handle_user_input(t_hterm **p_hterm, char c)
{
	if (c == ESC)
		handle_arrows(p_hterm);
	else if (c == EOT)
	{
		printf("exit\n");
		apply_term("RESET");
		exit(EXIT_SUCCESS);
	}
	else if (c == 0)
		reset_cmd(*p_hterm);
	else if (c == DEL)
		del_prev_char(*p_hterm);
	else if (c == CLEAR)
		;
	else if (c == '\n' || c == '\v')
		;
	else if (c == TAB)
		;
	else
		return (0);
	return (1);
}

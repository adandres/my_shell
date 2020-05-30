/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   handle_user_input.c                             /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:02:03 by adandres               /    /  /         */
/*   Updated: 2020/05/30 18:57:39 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static char	del_inline(t_hterm **p_hterm)
{
	int	i;
	char	tmp;
	char	prev;

	i = (*p_hterm)->pos;
	prev = 0;
	while (i >= 0)
	{
		tmp = (*p_hterm)->cmd[i];
		(*p_hterm)->cmd[i] = prev;
		if (i < (*p_hterm)->pos - (*p_hterm)->curs)
			break;
		prev = tmp;
		i--;
	}
	return (tmp);
}

static void	del_prev_char(t_hterm **p_hterm)
{
	char	del;
	int	a;

	a = 0;
	if ((*p_hterm)->curs + 1 > (*p_hterm)->pos)
		return;
	if ((*p_hterm)->curs == 0)
	{
		del = (*p_hterm)->cmd[(*p_hterm)->pos - 1];
		(*p_hterm)->cmd[(*p_hterm)->pos - 1] = '\0';
	}
	else
		del = del_inline(p_hterm);
	if (del == '\n')
	{
		my_printf("\x1b[J");
		my_printf(ARROW_UP);
		a = my_strinchr((*p_hterm)->cmd, (*p_hterm)->pos - (*p_hterm)->curs);
		if (a > 0)
			print_cursor_right(a);
	}
	else
		my_printf(DEL_PREV_CHAR);
	if ((*p_hterm)->curs)
		print_cmd(*p_hterm, 0);
	(*p_hterm)->pos -= 1;
}

static void		reset_cmd(t_hterm **p_hterm)
{
	my_bzero((*p_hterm)->cmd, my_strlen((*p_hterm)->cmd));
	(*p_hterm)->pos = 0;
	(*p_hterm)->curs = 0;
	(*p_hterm)->restart = 1;
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
		reset_cmd(p_hterm);
	else if (c == DEL)
		del_prev_char(p_hterm);
	else if (c == CLEAR)
		;
	else if (c == '\n' || c == '\v')
		;
	else if (c == TAB)
		;//auto completion
	else
		return (0);
	return (1);
}

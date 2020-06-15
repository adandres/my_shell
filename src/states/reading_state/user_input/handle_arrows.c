/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   handle_arrows.c                                 /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:23:38 by adandres               /    /  /         */
/*   Updated: 2020/06/15 14:35:19 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"



static void		delete_last_command(t_hterm **p_hterm)
{
	int	a;

	a = my_strcount((*p_hterm)->cmd + (*p_hterm)->curs, '\n');
	if (a > 0)
		print_cursor_up(a);
	print_cursor_left((*p_hterm)->pos + 3);
	my_printf("\x1b[J");
}

static void		print_new_command(t_hterm **p_hterm)
{
	my_printf("$> %s", (*p_hterm)->cmd);
	(*p_hterm)->pos = my_strlen((*p_hterm)->cmd);
	(*p_hterm)->curs = 0;
}

static void		get_prev_command(t_hterm **p_hterm)
{
	free((*p_hterm)->history[(*p_hterm)->hist]);
	(*p_hterm)->history[(*p_hterm)->hist] = my_strdup((*p_hterm)->cmd);
	(*p_hterm)->hist -= 1;
	if ((*p_hterm)->hist == -1)
	{
		free((*p_hterm)->cmd);
		(*p_hterm)->cmd = my_strdup((*p_hterm)->save);
		free((*p_hterm)->save);
		(*p_hterm)->save = NULL;
	}
	else
(*p_hterm)->cmd = my_strcpy((*p_hterm)->cmd, (*p_hterm)->history[(*p_hterm)->hist]);
}

static void		get_next_command(t_hterm **p_hterm)
{
	if ((*p_hterm)->hist == -1)
		(*p_hterm)->save = my_strdup((*p_hterm)->cmd);
	else
	{
		free((*p_hterm)->history[(*p_hterm)->hist]);
		(*p_hterm)->history[(*p_hterm)->hist] = my_strdup((*p_hterm)->cmd);
	}
	(*p_hterm)->hist += 1;
(*p_hterm)->cmd = my_strcpy((*p_hterm)->cmd, (*p_hterm)->history[(*p_hterm)->hist]);
}

void		handle_arrows(t_hterm **p_hterm)
{
	char	c;
	int	a;

	read(0, &c, 1);
	read(0, &c, 1);
	if (c == 'C' && (*p_hterm)->curs > 0)
	{
		get_cursor_position(p_hterm);
		get_terminal_size(p_hterm);
		if ((*p_hterm)->cmd[(*p_hterm)->pos - (*p_hterm)->curs] == '\n' || \
			(*p_hterm)->curs_pos.x == (*p_hterm)->win_lim.x)
		{
			print_cursor_left((*p_hterm)->win_lim.x);
			my_printf(ARROW_DOWN);
		}
		else
			my_printf(ARROW_RIGHT);
		(*p_hterm)->curs--;
	}
	if (c == 'D' && (*p_hterm)->curs < (*p_hterm)->pos)
	{
		get_cursor_position(p_hterm);
		get_terminal_size(p_hterm);
		if ((*p_hterm)->curs_pos.x == 1)
		{
	a = my_strinchr((*p_hterm)->cmd, (*p_hterm)->pos - (*p_hterm)->curs, (*p_hterm)->win_lim.x - 1);
			my_printf(ARROW_UP);
			if (a > 0)
				print_cursor_right(a);
		}
		else
			my_printf(ARROW_LEFT);
		(*p_hterm)->curs++;
	}
	if (c == 'A' && (*p_hterm)->hist < (*p_hterm)->h_len - 1)
	{
		delete_last_command(p_hterm);
		get_next_command(p_hterm);
		print_new_command(p_hterm);
	}
	if (c == 'B' && (*p_hterm)->hist > -1)
	{
		delete_last_command(p_hterm);
		get_prev_command(p_hterm);
		print_new_command(p_hterm);
	}
}

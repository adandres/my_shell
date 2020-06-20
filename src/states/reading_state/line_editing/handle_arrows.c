/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   handle_arrows.c                                 /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:23:38 by adandres               /    /  /         */
/*   Updated: 2020/06/20 19:47:26 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"



static void		delete_last_command(t_hterm *hterm)
{
	int	a;

	a = my_strcount(hterm->cmd + hterm->curs, '\n');
	if (a > 0)
		print_cursor_up(a);
	print_cursor_left(hterm->pos + 3);
	my_printf("\x1b[J");
}

static void		print_new_command(t_hterm *hterm)
{
	my_printf("$> %s", hterm->cmd);
	hterm->pos = my_strlen(hterm->cmd);
	hterm->curs_y = count_lines(hterm, 0);
	hterm->curs = 0;
}

static void		get_prev_command(t_hterm **p_hterm)
{
	t_hterm *hterm;

	hterm = *p_hterm;
	free(hterm->history[hterm->hist]);
	hterm->history[hterm->hist] = my_strdup(hterm->cmd);
	hterm->hist -= 1;
	free(hterm->cmd);
	if (hterm->hist == -1)
	{
		hterm->cmd = my_strdup(hterm->save);
		free(hterm->save);
		hterm->save = NULL;
	}
	else
		hterm->cmd = my_strdup(hterm->history[hterm->hist]);
	*p_hterm = hterm;
}

static void		get_next_command(t_hterm **p_hterm)
{
	t_hterm *hterm;

	hterm = *p_hterm;
	if (hterm->hist == -1)
		hterm->save = my_strdup(hterm->cmd);
	else
	{
		free(hterm->history[hterm->hist]);
		hterm->history[hterm->hist] = my_strdup(hterm->cmd);
	}
	hterm->hist += 1;
	free(hterm->cmd);
	hterm->cmd = my_strdup(hterm->history[hterm->hist]);
	*p_hterm = hterm;
}

void		handle_arrows(t_hterm **p_hterm)
{
	char	c;
	int	a;
	t_hterm	*hterm;

	read(0, &c, 1);
	read(0, &c, 1);
	hterm = *p_hterm;
	if (c == 'C' && hterm->curs > 0)
	{
		if (hterm->cmd[hterm->pos - hterm->curs] == '\n' || \
			hterm->curs_pos.x == hterm->win_lim.x)
		{
			my_printf(ARROW_DOWN);
			print_cursor_left(hterm->win_lim.x - 1);
			hterm->curs_y += 1;
		}
		else
			my_printf(ARROW_RIGHT);
		hterm->curs--;
	}
	if (c == 'D' && hterm->curs < hterm->pos)
	{
		if (hterm->curs_pos.x == 1)
		{
			a = count_rows(hterm);
			my_printf(ARROW_UP);
			if (a > 0)
				print_cursor_right(a);
			hterm->curs_y -= 1;
		}
		else
			my_printf(ARROW_LEFT);
		hterm->curs++;
	}
	if (c == 'A' && hterm->hist < hterm->h_len - 1)
	{
		delete_last_command(hterm);
		get_next_command(&hterm);
		print_new_command(hterm);
	}
	if (c == 'B' && hterm->hist > -1)
	{
		delete_last_command(hterm);
		get_prev_command(&hterm);
		print_new_command(hterm);
	}
	*p_hterm = hterm;
}

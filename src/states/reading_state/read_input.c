/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   read_input.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 18:22:49 by adandres               /    /  /         */
/*   Updated: 2020/05/23 19:59:53 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	my_strcount(char *str, char c)
{
	int	i;
	int	nb;
	
	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == c)
			nb++;
		i++;
	}
	return (nb);
}

void	history(char ***p_history, char *cmd);

t_term	init_term(t_term term)
{
	if (tcgetattr(0, &term) == -1)
	{
		dprintf(2, "error tecgedwed\n");
		return (term);
	}
	return (term);
}

t_term	canon_input(t_term term)
{
	term.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		dprintf(2, "failed to put in raw mode\n");
	return (term);
}

t_term	reset_term(t_term backup)
{
	if (tcsetattr(0, 0, &backup) == -1)
		dprintf(2, "reset failed\n");
	my_putstr(SHOW_CURSOR);
	return (backup);
}

void	apply_term(char *op)
{
	static t_term	term;
	static t_term	term_backup;

	if (my_strequ(op, "INIT"))
	{
		term = init_term(term);
		term_backup = init_term(term_backup);
	}
	else if (my_strequ(op, "ROW"))
		term = canon_input(term);
	else if (my_strequ(op, "RESET"))
		term = reset_term(term_backup);
}

int		resize(char **str, int n)
{
	char	*new;
	char	*tmp;

	new = NULL;
	tmp = NULL;
	if (n == 0)
	{
		*str = (char*)malloc(sizeof(char) * 64);
		my_bzero(*str, 64);
		return (64);
	}
	n += 1;
	n *= 2;
	new = (char*)malloc(sizeof(char) * n);
	my_bzero(new, n);
	tmp = *str;
	my_strcpy(new, *str);
	*str = new;
	free(tmp);
	return (n);
}

void		print_cmd(t_hterm *hterm)
{
	if (hterm->curs)
		my_printf("\x1b[K");
	my_printf("%s", hterm->cmd + hterm->pos - hterm->curs - 1);
	if (hterm->curs)
		my_printf("\x1b[%dD", hterm->curs);
}

void	del_prev_char(t_hterm **p_hterm)
{
	int	i;
	char	tmp;
	char	prev;

	i = (*p_hterm)->pos - 1;
	prev = 0;
	if ((*p_hterm)->pos == 0)
		return;
	if ((*p_hterm)->curs == 0)
		(*p_hterm)->cmd[(*p_hterm)->pos - 1] = '\0';
	else
	{
		while (i >= 0)
		{
			tmp = (*p_hterm)->cmd[i];
			(*p_hterm)->cmd[i] = prev;
			if (i < (*p_hterm)->pos - (*p_hterm)->curs)
				break;
			prev = tmp;
			i--;
		}
	}
	my_printf(DEL_PREV_CHAR);
	if ((*p_hterm)->curs)
		print_cmd(*p_hterm);
	(*p_hterm)->pos -= 1;
}

void		read_esc(t_hterm **p_hterm)
{
	char c;

	read(0, &c, 1);
	read(0, &c, 1);
	if (c == 'C' && (*p_hterm)->curs > 0)
	{
		my_printf(ARROW_RIGHT);
		(*p_hterm)->curs--;
	}
	if (c == 'D' && (*p_hterm)->curs < (*p_hterm)->pos)
	{
		my_printf(ARROW_LEFT);
		(*p_hterm)->curs++;
	}
	if (c == 'A' && (*p_hterm)->hist < (*p_hterm)->h_len - 1)
	{
		if (my_strcount((*p_hterm)->cmd, '\n'))
		my_printf("\x1b[%dA", my_strcount((*p_hterm)->cmd, '\n'));
		if ((*p_hterm)->hist == -1)
			(*p_hterm)->save = my_strdup((*p_hterm)->cmd);
		else
		{
		free((*p_hterm)->history[(*p_hterm)->hist]);
		(*p_hterm)->history[(*p_hterm)->hist] = my_strdup((*p_hterm)->cmd);
		}
		(*p_hterm)->hist += 1;
(*p_hterm)->cmd = my_strcpy((*p_hterm)->cmd, (*p_hterm)->history[(*p_hterm)->hist]);
		my_printf("\x1b[%dD", (*p_hterm)->pos + 3);
				my_printf("\x1b[J");
		my_printf("$> %s", (*p_hterm)->cmd);
		(*p_hterm)->pos = my_strlen((*p_hterm)->cmd);
		(*p_hterm)->curs = 0;
	}
	if (c == 'B' && (*p_hterm)->hist > -1)
	{
		if (my_strcount((*p_hterm)->cmd, '\n'))
		my_printf("\x1b[%dA", my_strcount((*p_hterm)->cmd, '\n'));
		free((*p_hterm)->history[(*p_hterm)->hist]);
		(*p_hterm)->history[(*p_hterm)->hist] = my_strdup((*p_hterm)->cmd);
		(*p_hterm)->hist -= 1;
			if ((*p_hterm)->hist == -1)
		{
			(*p_hterm)->cmd = my_strcpy((*p_hterm)->cmd, (*p_hterm)->save);
			free((*p_hterm)->save);
		}
		else
(*p_hterm)->cmd = my_strcpy((*p_hterm)->cmd, (*p_hterm)->history[(*p_hterm)->hist]);
		my_printf("\x1b[%dD", (*p_hterm)->pos + 3);
		my_printf("\x1b[J");
		my_printf("$> %s", (*p_hterm)->cmd);
		(*p_hterm)->pos = my_strlen((*p_hterm)->cmd);
		(*p_hterm)->curs = 0;
	}
}

void		reset_cmd(t_hterm **p_hterm)
{
	my_bzero((*p_hterm)->cmd, my_strlen((*p_hterm)->cmd));
	(*p_hterm)->pos = 0;
	(*p_hterm)->pos = 0;
	(*p_hterm)->restart = 1;
}

int		is_special_char(t_hterm **p_hterm, char c)
{
	if (c == ESC)
		read_esc(p_hterm);
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
		;//state_m = pre_complete(state_m, pos);
	else
		return (0);
	return (1);
}

void	add_char_at_curs(t_hterm **p_hterm, char input)
{
	t_hterm *hterm;
	int	i;
	char	tmp;

	i = 1;
	hterm = *p_hterm;
	tmp = hterm->cmd[hterm->pos - hterm->curs];
	hterm->cmd[hterm->pos - hterm->curs] = input;
	while (hterm->curs - i >= 0)
	{
		input = hterm->cmd[hterm->pos - hterm->curs + i];
		hterm->cmd[hterm->pos - hterm->curs + i] = tmp;
		tmp = input;
		i++;
	}
}

void	get_cmd(t_hterm **p_hterm)
{
	t_hterm		*hterm;
	int		size;
	char		input;

	hterm = *p_hterm;
	input = 0;
	size = resize(&hterm->cmd, 0);
	apply_term("ROW");
	while (input != '\n' && (isatty(0) || input) && !hterm->restart)
	{
		if (my_isprint(input))
			print_cmd(hterm);
		if (read(STDIN_FILENO, &input, 1) < 0)
			printf("error\n");
		else
		{
			if (!is_special_char(&hterm, input))
			{
				if (hterm->pos == size)
					size = resize(&hterm->cmd, size);
				if (hterm->curs == 0)
					hterm->cmd[hterm->pos] = input;
				else
					add_char_at_curs(&hterm, input);
				hterm->pos += 1;
			}
		}
	}
	apply_term("RESET");
	if (hterm->restart == 0)
		printf("\n");
}

t_hterm		*init_term_handling_struct(t_state *machine)
{
	t_hterm		*hterm;

	if (!(hterm = (t_hterm*)malloc(sizeof(t_hterm))))
		return (NULL);
	hterm->history = machine->history;
	hterm->pos = 0;
	hterm->curs = 0;
	hterm->hist = -1;
	hterm->h_len = my_tablen(hterm->history);
	hterm->restart = 0;
	hterm->nrl = 0;
	return (hterm);
}

char		*get_input(t_state *machine)
{
	t_hterm *hterm;
	char	*input;

	my_printf("> ");
	hterm = init_term_handling_struct(machine);
	get_cmd(&hterm);
	input = hterm->cmd;
	free(hterm);
	return (input);
}

void		re_read_input(t_state **machine)
{
	char	*input;
	t_hterm	*hterm;

	hterm = init_term_handling_struct(*machine);
	input = NULL;
	my_printf("> ");
	if ((*machine)->cmd)
		input = my_strjoin_free((*machine)->cmd, "\n");
	get_cmd(&hterm);
	(*machine)->history = hterm->history;
	if (hterm->pos == 0)
	{
		(*machine)->cmd = input;
		return;
	}
	if (input)
		input = my_strjoin_free(input, hterm->cmd);
	else
		input = my_strdup(hterm->cmd);
	free(hterm->cmd);
	free(hterm);
	(*machine)->cmd = input;
}

void		read_input(t_state **machine)
{
	t_hterm		*hterm;

	hterm = init_term_handling_struct(*machine);
	my_printf("\x1b[2K");
	my_printf("\x1b[%dD", 3);
	if (isatty(STDIN_FILENO))
		my_printf("$> ");
	get_cmd(&hterm);
	(*machine)->cmd = hterm->cmd;
	(*machine)->history = hterm->history;
	free(hterm);
	if ((*machine)->cmd != NULL)
		(*machine)->state = PARSE;
	else if (isatty(0) == 0)
		exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cmd.c                                       /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:58:27 by adandres               /    /  /         */
/*   Updated: 2020/05/30 18:55:36 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int		resize(char **str, int n)
{
	char	*new;

	new = NULL;
	if (n == 0)
	{
		*str = (char*)malloc(sizeof(char) * 16);
		my_bzero(*str, 16);
		return (16);
	}
	n *= 2;
	new = (char*)malloc(sizeof(char) * n);
	my_bzero(new, n);
	new = my_strcpy(new, *str);
	//free(*str);
	*str = new;
	return (n);
}

static void	add_char_at_curs(t_hterm **p_hterm, char input)
{
	t_hterm	*hterm;
	int	i;
	char	tmp;

	i = 1;
	hterm = *p_hterm;
	tmp = hterm->cmd[hterm->pos - hterm->curs];
	hterm->cmd[hterm->pos - hterm->curs] = input;
	while (hterm->pos - hterm->curs + i <= hterm->pos + 1)
	{
		input = hterm->cmd[hterm->pos - hterm->curs + i];
		hterm->cmd[hterm->pos - hterm->curs + i] = tmp;
		tmp = input;
		i++;
	}
}

static void	cursor_at_end(t_hterm **p_hterm)
{
	int	a;

	if ((*p_hterm)->curs == 0 || (*p_hterm)->pos == 0)
		return;
	a = my_strcount((*p_hterm)->cmd + (*p_hterm)->pos - (*p_hterm)->curs, '\n');
	my_printf("\x1b[%dB", a);
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
			print_cmd(hterm, 1);
		if (read(STDIN_FILENO, &input, 1) < 0)
			printf("error\n");
		else
		{
			if (!handle_user_input(&hterm, input))
			{
				if (hterm->pos == size - 2)
					size = resize(&hterm->cmd, size);
				if (hterm->curs == 0)
					hterm->cmd[hterm->pos] = input;
				else
					add_char_at_curs(&hterm, input);
				hterm->pos += 1;
			}
			else if ((int)my_strlen(hterm->cmd) >= size)
			{
				while (size <= (int)my_strlen(hterm->cmd))
					size *= 2;
				size = resize(&hterm->cmd, size);
			}
		}
	}
	apply_term("RESET");
	cursor_at_end(p_hterm);
	if (hterm->restart == 0)
		printf("\n");
}

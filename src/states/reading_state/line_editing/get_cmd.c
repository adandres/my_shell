/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_cmd.c                                       /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:58:27 by adandres               /    /  /         */
/*   Updated: 2020/06/20 17:18:14 by adandres                                 */
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
	free(*str);
	*str = new;
	return (n);
}

static void	add_char_at_curs(t_hterm *hterm, char input)
{
	int	i;
	char	tmp;

	i = 1;
	tmp = hterm->cmd[hterm->pos - hterm->curs];
	hterm->cmd[hterm->pos - hterm->curs] = input;
	while (hterm->pos - hterm->curs + i <= hterm->pos)
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

	input = 0;
	hterm = *p_hterm;
	size = resize(&hterm->cmd, 0);
	my_printf("\x1b[7h");
	apply_term("ROW");
	get_info(hterm);
	while (input != '\n' && (isatty(0) || input) && !hterm->restart)
	{
		if (read(STDIN_FILENO, &input, 1) < 0)
			printf("error\n");
		else
		{
			if (!handle_user_input(&hterm, input))
			{
				if (hterm->pos >= size - 2)
					size = resize(&hterm->cmd, size);
				add_char_at_curs(hterm, input);
				print_cmd(hterm, 1);
				hterm->pos += 1;
			}
			else if ((int)my_strlen(hterm->cmd) >= size)
			{
				while (size <= (int)my_strlen(hterm->cmd))
					size *= 2;
				size = resize(&hterm->cmd, size);
			}
			get_info(hterm);
		}
	}
	apply_term("RESET");
	place_cursor_at_end(hterm);
	if (hterm->restart == 0)
		printf("\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_word.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 00:31:31 by adandres               /    /  /         */
/*   Updated: 2020/07/11 16:48:13 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"


static int check_separator(char c)
{
	if ((check_special_char(c) == 0))
		return (0);
	if (check_sep(c, " \t\n"))
		return (0);
	return (1);
}

static int get_match(char *input, int i, int j)
{
	while (input[i])
	{
		if (input[i] == ')' && i > j)
			return (i);
		i++;
	}
	return (0);
}

int     check_word(t_token **token, char *input)
{
	int i;
	int j;
	int quotes;

	i = 0;
	j = 0;
	quotes = 0;
	while ((check_separator(input[i]) || quotes || i < j) && input[i])
	{
		quotes = check_quotes(input[i], quotes);
		if (input[i] == '(' && quotes == 0)
			j = get_match(input, i, j);
		i++;
	}
	if (i > 0 && my_strnchr(input, i, '=') == 0)
		*token = create_token(my_strndup(input, i), WORD);
	else if (i > 0 && my_strnchr(input, i, '=') != 0)
		*token = create_token(my_strndup(input, i), SENV);
	else
		return (-1);
	return (i);
}

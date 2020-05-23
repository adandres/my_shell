/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_word.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 00:31:31 by adandres               /    /  /         */
/*   Updated: 2020/04/22 21:16:24 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"


static int check_separator(char c)
{
	if ((check_special_char(c) == 0))
		return (0);
	if (c == ' ' || c == '\t' || c == '\n')
		return (0);
	return (1);
}

int     check_word(t_token **token, char *input)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while ((check_separator(input[i]) || quotes) && input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && \
				(quotes == 0 || quotes == input[i]))
			quotes = ((quotes == 0) ? input[i] : 0);
		i++;
	}
	if (i > 0)
		*token = create_token(my_strndup(input, i), WORD);
	if (i == 0)
		return (-1);
	return (i);
}

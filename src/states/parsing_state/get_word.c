/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_word.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 00:31:31 by adandres               /    /  /         */
/*   Updated: 2020/04/19 01:19:57 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int check_separator(char c)
{
	if (c != 0 && check_special_char(c) && c != ' ' && c != '\t')
		return (1);
	return (0);
}

static int     check_word(t_token **token, char *input)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while (check_separator(input[i]) || quotes)
	{
		if ((input[i] == '\'' || input[i] == '\"') && \
				(quotes == 0 || quotes == input[i]))
			quotes = ((quotes == 0) ? input[i] : 0);
		i++;
	}
	if (i > 0)
		*token = create_token(my_strndup(input, i), WORD);
	return (i);
}

int	get_word(t_token **token, char *input, int last)
{
	int		len;


	len = check_redir(token, input);
	if (len > 0)
		return (len);
	if (last == R_ICL || last == R_OCL)
	{
		*token = create_token(my_strdup("-"), WORD);
		return (1);
	}
	if ((len = check_word(token, input)) > 0)
		return (len);
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_word.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 00:31:31 by adandres               /    /  /         */
/*   Updated: 2020/04/21 19:05:53 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	check_filename(char *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (0);
	while (input[i])
	{
		if (check_special_char(input[i]) == 0)
			return (0);
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

static int check_separator(char c)
{
	if ((check_special_char(c) == 0))
		return (0);
	if (c == ' ' || c == '\t' || c == '\n')
		return (0);
	return (1);
}

int		check_bad_charactere(char *input)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (input[i])
	{	
		if ((input[i] == '\'' || input[i] == '\"') && \
				(quotes == 0 || quotes == input[i]))
			quotes = ((quotes == 0) ? input[i] : 0);
		if (quotes == 0 && check_broke_char(input[i]))
			return (1);
		i++;
	}
	return (0);
}

static int     check_word(t_token **token, char *input)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	printf("1\n");
	if (input == NULL)
		return (0);
	while ((check_separator(input[i]) || quotes) && input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && \
				(quotes == 0 || quotes == input[i]))
			quotes = ((quotes == 0) ? input[i] : 0);

			i++;
	}
	printf("1\n");
	if (i > 0)
		*token = create_token(my_strndup(input, i), WORD);
	printf("1\n");
	//my_putendl((*tokan)->data);
	//my_printf("td:		\n%S\n", (*token)->data);
	printf("1\n");
	return (i);
}

int	get_word(t_token **token, char *input, int last)
{
	int		len;

	if (check_bad_charactere(input))
	{
		//fprintf(stderr, "error: %s\n", input);
		return (-1);
	}
	len = check_redir(token, input);
	if (len && (input[len - 1] == '<' || input[len - 1] == '>')) \
	{
		if (check_filename(input + len) == 0)
			print_token_error(input[len]);
		else
			return (len);
		return (-1);
	}
	if (len)
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

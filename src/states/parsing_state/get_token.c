/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_token.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 19:41:57 by adandres               /    /  /         */
/*   Updated: 2020/07/11 14:32:58 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	get_word(t_token **token, char *input, int last);

static int		ret_semi(t_token **token, char *input)
{
	if (input[0] == ';')
	{
		*token = create_token(my_strdup(";"), SEMI);
		return (1);
	}
	return (0);
}

static int		ret_pipe(t_token **token, char *input)
{
	 if (input[0] == '|' && input[1] != '|')
	{
		*token = create_token(my_strdup("|"), PIPE);
		return (1);
	}
	return (0);
}

static int		ret_lor(t_token **token, char *input)
{
	if (input[0] == '|' && input[1] == '|')
	{
		*token = create_token(my_strdup("||"), L_OR);
		return (2);
	}
	return (0);
}

static int		ret_land(t_token **token, char *input)
{
	if (input[0] == '&' && input[1] == '&')
	{
		*token = create_token(my_strdup("&&"), L_AND);
		return (2);
	}
	return (0);
}

int	get_del(t_token **token, char *input)
{
	int		i;
	int		len;
	int		(*func[4])(t_token **, char*) = {&ret_semi, &ret_pipe, \
			&ret_lor, &ret_land};

	i = 0;
	len = 0;
	while (len == 0 && i < 4)
		len = func[i++](token, input);
	return (len);
}

int	check_word(t_token **token, char *input);

int	get_token(t_token **token, char *input, int last)
{
	int	i;
	int	len;
	int	(*get[3])(t_token **,char *) = {&get_del, &check_redir, &check_word};

	i = 0;
	len = 0;
	if (last == R_ICL || last == R_OCL)
	{
		*token = create_token(my_strdup("-"), WORD);
		return (1);
	}
	while (i < 3 && len == 0)
		len = get[i++](token, input);
	return (len);
}

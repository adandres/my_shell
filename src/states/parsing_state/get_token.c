/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_token.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 19:41:57 by adandres               /    /  /         */
/*   Updated: 2020/04/19 01:03:52 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	get_word(t_token **token, char *input, int last);

static t_token		*ret_semi(char *input)
{
	if (input[0] == ';')
		return (create_token(my_strdup(";"), SEMI));
	return (NULL);
}

static t_token		*ret_pipe(char *input)
{
	 if (input[0] == '|' && input[1] != '|')
		return (create_token(my_strdup("|"), PIPE));
	return (NULL);
}

static t_token		*ret_lor(char *input)
{
	if (input[0] == '|' && input[1] == '|')
		return (create_token(my_strdup("||"), L_OR));
	return (NULL);
}

static t_token		*ret_land(char *input)
{
	if (input[0] == '&' && input[1] == '&')
		return (create_token(my_strdup("&&"), L_AND));
	return (NULL);
}

int	get_token(t_token **token, char *input, int last)
{
	int		i;
	t_token		*(*func[4])(char*) = {&ret_semi, &ret_pipe, &ret_lor, &ret_land};
	
	i = 0;
	*token = NULL;
	while (*token == NULL && i < 4)
		*token = func[i++](input);
	if (*token == NULL)
		return (get_word(token, input, last));
	return (my_strlen((*token)->data));
}

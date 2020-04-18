/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   check_redir.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 19:47:36 by adandres               /    /  /         */
/*   Updated: 2020/04/19 00:54:40 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	pass_number(char *input)
{
	int i;

	i = 0;
	while (input[i] >= '0' && input[i] <= '9')
		i++;
	return (i);
}

static int	give_type(char input)
{

	if (input == '>')
		return (R_OUT);
	else if (input == '<')
		return (R_IN);
	return (0);
}

static int	first_redir(t_token **token, char *input)
{
	if (input[0] == '&' && input[1] == '>')
	{
		*token = create_token(my_strndup(input, 1), R_ER);
		return (2);
	}
	return (0);
}

static t_token	*pet_token(char *input, int type)
{
	if (type == R_OUT)
		return (create_token(input, RA_OUT));
	return (create_token(input, R_RW));
}

static int	ret_in(t_token **token, char *input)
{
	int	i;
	int	type;

	i = pass_number(input);
	if ((type = give_type(input[i])))
		i++;
	if (input[i] == '>')
	{
		if (check_special_char(input[i + 1]) == 1)
		{
			*token = pet_token(my_strndup(input, i + 1), type);
			return (i + 1);
		}
	}
	return (0);
}

static int	sec_redir(t_token **token, char *input)
{
	int	i;
	int	type;

	i = pass_number(input);
	if ((type = give_type(input[i])))
		i++;
	if (input[i] == '<' && type == R_IN)
	{
		if (check_special_char(input[i + 1]) == 1)
		{
			*token = create_token(my_strndup(input, i), R_DOC);
			return (i);
		}
	}
	return (0);
}

static int	ret_token(t_token **token, char *input)
{
	int	i;
	int	type;

	i = pass_number(input);
	if (!(type = give_type(input[i])))
		return (0);
	if (input[++i] == '&')
	{
		i++;
		while (input[i] == ' ' && input[i])
			i++;
		if (input[i] == '-' && type == R_OUT)
			type = R_OCL;
		else if (input[i] == '-')
			type = R_ICL;
		*token = create_token(my_strndup(input, i), type);
		return (i);
	}
	return (0);
}

static int	ret_stoken(t_token **token, char *input)
{
	int	i;
	int	type;
	
	i = pass_number(input);
	if (!(type = give_type(input[i])))
		return (0);
	*token = create_token(my_strndup(input, i), type);
	return (i + 1);
}

static int	is_redir(char *input)
{
	int	i;

	i = pass_number(input);
	if (input[i] == '\0')
		return (0);
	return (1);
}

int		check_redir(t_token **token, char *input)
{
	int len;
	int i;
	int	(*func[5])(t_token**, char*) = {&first_redir, &ret_in, &sec_redir, \
						&ret_token, &ret_stoken}; 

	i = 0;
	len = 0;
	if (is_redir(input) == 0)
		return (0);
	while (len == 0 && i < 5)
		len = func[i++](token, input);
	return (len);
}

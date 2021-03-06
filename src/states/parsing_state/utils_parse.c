/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   utils_parse.c                                   /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 00:41:08 by adandres               /    /  /         */
/*   Updated: 2020/07/11 14:46:46 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	print_list(t_list *list, int print_type)
{
	t_token		*token;
	char		*str;

	while (list != NULL)
	{
		token = (t_token*)list->content;
		str = token->content;
		if (print_type)
			printf("%d", token->type);
		else
			printf("%s", str);
		if (list->next)
			printf(" --> ");
		list = list->next;
	}
	printf("\n");
}

t_token		*create_token(char *input, int type)
{
	t_token	*token;

	token = (t_token*)malloc(sizeof(t_token));
	token->type = type;
	token->content = input;
	return (token);
}

int check_special_char(char c)
{
        if (c != ';' && c != '|' && c != '>' && c != '!'\
        && c != '<' && c != '&')
                return (1);
        return (0);
}

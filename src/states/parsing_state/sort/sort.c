/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   sort.c                                          /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/22 16:07:19 by adandres               /    /  /         */
/*   Updated: 2020/07/11 11:42:05 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	expand_redir(t_list **token_list);

void	sort_token(t_list **token_list, int is_debug)
{
	my_lst_reverse(token_list);
	if (is_debug)
	{
		printf("input_list: ");
		print_list(*token_list, 0);
		printf("type__list: ");
		print_list(*token_list, 1);
		printf("\n");
	}
	assign_word(token_list);
	first_is_cmd(token_list, 0);
	if (is_debug)
	{
		printf("input_list: ");
		print_list(*token_list, 0);
		printf("type__list: ");
		print_list(*token_list, 1);
		printf("\n");
	}
	sort_list(token_list);
	if (is_debug)
	{
		printf("input_list: ");
		print_list(*token_list, 0);
		printf("type__list: ");
		print_list(*token_list, 1);
		printf("\n");
	}
	reverse_redir(token_list);
	if (is_debug)
	{
		printf("input_list: ");
		print_list(*token_list, 0);
		printf("type__list: ");
		print_list(*token_list, 1);
		printf("\n");
	}
	expand_redir(token_list);
	if (is_debug)
	{
		printf("input_list: ");
		print_list(*token_list, 0);
		printf("type__list: ");
		print_list(*token_list, 1);
		printf("\n");
	}
	my_lst_reverse(token_list);
}


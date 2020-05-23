/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   error.c                                         /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/19 16:05:09 by adandres               /    /  /         */
/*   Updated: 2020/04/22 15:16:05 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void	no_mem_error(void)
{
	my_putendl("Cannot allocate memory");
	exit(EXIT_FAILURE);
}

void	print_no_found(t_cmd *cmd)
{
	fprintf(stderr, "shell: %s: command not found\n", cmd->argv[0]);
}

void	print_token_error(char c)
{
	if (c != '\n' && c)
		fprintf(stderr, "shell: syntax error near unexpected token `%c'\n", c);
	else
		fprintf(stderr, "shell: syntax error near unexpected token `newline'\n");
}

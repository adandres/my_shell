/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   check_quotes.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/30 16:29:32 by adandres               /    /  /         */
/*   Updated: 2020/07/11 12:14:38 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	check_quotes(char input, int quoted)
{
	if ((input == '\'' || input == '\"') && (quoted == 0 || quoted == input))
			return ((quoted == 0) ? input : 0);
	return (quoted);
}

int	not_a_del(char c)
{
	if (c != ' ' && c != '\n' && c != '\v' && c != 0)
		return (1);
	return (0);
}

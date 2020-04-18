/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strjoin_tab.c                                /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/18 19:29:00 by adandres               /    /  /         */
/*   Updated: 2020/04/18 19:29:45 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "libme.h"

char		*my_strjoin_tab(char **argv, char *del)
{
	int	i;
	char	*input;

	input = my_strdup(argv[0]);
	i = 1;
	while (argv[i])
	{
		input = my_strjoin_free(input, del);
		input = my_strjoin_free(input, argv[i]);
		i++;
	}
	return (input);
}

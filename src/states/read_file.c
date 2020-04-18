/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   read_file.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 19:11:41 by adandres               /    /  /         */
/*   Updated: 2020/04/18 17:29:53 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void    read_file(t_state **machine)
{
	char	*str;
	int	ret;

	if ((ret = get_next_line((*machine)->file_fd, &str)) >= 0)
	{
		if (my_strlen(str) > 0)
		{
			(*machine)->cmd = my_strdup(str);
			(*machine)->state = PARSE;
		}
		if (ret > 0)
			free(str);
		if (ret == 0)
			exit(EXIT_SUCCESS);
	}	
	else
		exit(EXIT_FAILURE);
}

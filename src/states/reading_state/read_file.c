/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   read_file.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 19:11:41 by adandres               /    /  /         */
/*   Updated: 2020/05/14 13:15:51 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void    read_file(t_state **machine)
{
	char	*str;
	int	ret;
	
	(*machine)->cmd = NULL;
	if ((ret = get_next_line((*machine)->file_fd, &str)) >= 0)
	{
		if (ret > 0 && my_strlen(str) > 0)
		{
			(*machine)->cmd = my_strdup(str);
			(*machine)->state = PARSE;
		}
		if (ret > 0)
			free(str);
		if (ret == 0)
			/*while(1);*/exit(EXIT_SUCCESS);
	}
	else
		exit(EXIT_FAILURE);
}

void	re_read_file(t_state **machine)
{
	char	*command;

	command = NULL;
	if ((*machine)->cmd)
	{
		command = my_strdup((*machine)->cmd);
		free((*machine)->cmd);
	}
	read_file(machine);
	if (command && (*machine)->cmd)
	{
		command = my_strjoin_free(command, (*machine)->cmd);
		free((*machine)->cmd);
		(*machine)->cmd = command;
	}
	else if (command)
		(*machine)->cmd = my_strjoin_free(command, "\n");
}

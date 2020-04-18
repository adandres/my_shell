/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   utils.c                                         /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/30 16:46:29 by adandres               /    /  /         */
/*   Updated: 2020/04/02 16:10:22 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

void		cut_zero(char **ptr)
{
	char	*cutted;
	char	*to_cut;
	int	i;
	
	i = 0;
	to_cut = *ptr;
	while (to_cut[i] == '0')
		i++;
	if (i == 0)
		return ;
	if (to_cut[i] == '\0')
		return ;
	cutted = my_strdup(to_cut + i);
	free(*ptr);
	*ptr = cutted;
}

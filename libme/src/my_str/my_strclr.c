/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strclr.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 18:52:35 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:16:33 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

void	my_strclr(char *s)
{
	while (s != NULL && *s)
		*s++ = '\0';
}

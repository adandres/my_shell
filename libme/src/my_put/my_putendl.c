/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_putendl.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 11:38:26 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:55:26 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_put.h"

void		my_putendl(char const *s)
{
	my_putendl_fd(s, 1);
}
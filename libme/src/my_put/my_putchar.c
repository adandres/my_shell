/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_putchar.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 11:35:28 by adandres               /    /  /         */
/*   Updated: 2020/03/17 13:55:06 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_put.h"

void		my_putchar(char c)
{
	my_putchar_fd(c, 1);
}
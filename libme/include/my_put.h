/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_put.h                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 11:46:59 by adandres               /    /  /         */
/*   Updated: 2020/03/16 13:12:39 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_PUT_H
# define MY_PUT_H

# include <unistd.h>

void	my_putchar(char c);
void	my_putchar_fd(char c, int fd);
void	my_putendl(char const *s);
void	my_putendl_fd(char const *s, int fd);
void	my_putnbr(int n);
void	my_putnbr_fd(int n, int fd);
void	my_putstr(char const *s);
void	my_putstr_fd(char const *s, int fd);

#endif

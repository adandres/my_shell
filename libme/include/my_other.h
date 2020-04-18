/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_other.h                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/22 14:37:36 by adandres               /    /  /         */
/*   Updated: 2020/04/06 19:11:09 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_OTHER_H
# define MY_OTHER_H

#include <stdint.h>
#include <stdlib.h>
# define BUFF_SIZE 200

int		my_toupper(int c);
int		my_tolower(int c);
char		*my_itoa(intmax_t n);
char		*my_uitoa_base(uintmax_t nbr, char *base);
char		*my_uitoa(uintmax_t n);
int		my_atoi(const char *str);
int				get_next_line(const int fd, char **line);

#endif

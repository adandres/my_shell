/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_mem.h                                        /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 18:00:03 by adandres               /    /  /         */
/*   Updated: 2020/04/18 19:35:18 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MEM_H
# define MY_MEM_H

# include <stdlib.h>

void		*my_memalloc(size_t size);
void		*my_memccpy(void *dst, const void *src, int c, size_t size);
void		*my_memchr(const void *s, int c, size_t n);
int		my_memcmp(const void *s1, const void *s2, size_t n);
void		*my_memcpy(void *s1, const void *s2, size_t n);
void		my_memdel(void **ap);
void		*my_memmove(void *dst, const void *src, size_t n);
void		*my_memset(void *b, int c, size_t len);
void		my_bzero(void *s, size_t n);
void		*my_realloc(void *ptr, size_t c, size_t n);
void		my_memswap(void **a, void **b);

#endif

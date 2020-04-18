/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_addr.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/30 16:48:44 by adandres               /    /  /         */
/*   Updated: 2020/03/31 14:11:59 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

static char	dec_to_hex(int v)
{
	if (v >= 0 && v < 10)
		return '0' + v;
	else
		return 'a' + v - 10;
}

static char	*trad_addr(void *addr)
{
	long	conv;
	char	*trad;
	int	i;
	int	j;

	conv = (long)addr;
	i = (sizeof(conv) * 8) - 4;
	j = 0;
	trad = (char*)malloc(sizeof(char) * ((i / 4) + 2));
	while (i >= 0)
	{
		trad[j] = dec_to_hex((conv >> i) & 0xf);
		i -= 4;
		j++;
	}
	trad[j] = '\0';
	return (trad);
}

char		*get_addr(char f, t_print *pstrut, va_list ap)
{
	void	*ptr;
	char	*trad;

	if (f != 'p')
		return (NULL);
	ptr = va_arg(ap, void*);
	trad = trad_addr(ptr);
	cut_zero(&trad);
	(*pstrut).done = 1;
	(*pstrut).options.is_not_dec = 1;
	(*pstrut).options.nd_prefix = 1;
	(*pstrut).options.is_preffix = 2;
	return (trad);
}

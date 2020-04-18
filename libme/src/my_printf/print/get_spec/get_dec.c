/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_dec.c                                       /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/25 19:22:32 by adandres               /    /  /         */
/*   Updated: 2020/04/02 16:35:10 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

static void			fill_prefix(char *trad, t_print *pstrut)
{
	t_print strut;

	strut = *pstrut;
	strut.options.is_number = 1;
	if (trad[0] == '-')
	{
		strut.options.preffix = '-';
		strut.options.is_neg = 1;
	}
	else if (strut.flags.is_splus && !(strut.flags.is_zero))
		strut.options.preffix = '+';
	else if (strut.flags.is_space)
		strut.options.preffix = ' ';
	if (strut.options.preffix)
		strut.options.is_preffix = 1;
	*pstrut = strut;
}

static intmax_t		get_nbr(va_list ap, t_print strut)
{
	if (strut.specs.z)
                return (va_arg(ap, size_t));
        if (strut.specs.lng > 1)
                return (va_arg(ap, long long));
        if (strut.specs.j)
                return (va_arg(ap, intmax_t));
        if (strut.specs.lng == 1)
                return (va_arg(ap, long));
        if (strut.specs.shrt == 1)
                return ((short)va_arg(ap, int));
        if (strut.specs.shrt > 1)
                return ((char)va_arg(ap, int));
	return (va_arg(ap, int));
}

char			*get_dec(char f, t_print *pstrut, va_list ap)
{
	char		*trad;
	intmax_t	nbr;

	if (f != 'd' && f != 'i')
		return (NULL);
	nbr = get_nbr(ap, *pstrut);
	trad = my_itoa(nbr);
	cut_zero(&trad);
	if (trad == NULL)
		return (NULL);
	fill_prefix(trad, pstrut);
	(*pstrut).done = 1;
	return (trad);
}

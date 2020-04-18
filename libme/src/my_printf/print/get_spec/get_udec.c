/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_udec.c                                      /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/25 19:22:32 by adandres               /    /  /         */
/*   Updated: 2020/04/02 16:35:19 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

static void			fill_prefix(char f, t_print *pstrut)
{
	t_print strut;

	strut = *pstrut;
	strut.options.is_number = 1;
	if (f != 'u')
		strut.options.is_not_dec = 1;
	if (f == 'x' && strut.flags.is_htag)
		strut.options.nd_prefix = 1;
	if (f == 'X' && strut.flags.is_htag)
		strut.options.nd_prefix = 2;
	if (f == 'o' && strut.flags.is_htag) 
		strut.options.nd_prefix = 3;
	if (strut.flags.is_splus && !(strut.flags.is_zero) && !strut.options.is_not_dec)
		strut.options.preffix = '+';
	else if (strut.flags.is_space && !strut.options.is_not_dec)
		strut.options.preffix = ' ';
	if (strut.options.preffix)
		strut.options.is_preffix = 1;
	if (strut.options.nd_prefix && f != 'u')
		strut.options.is_preffix = 2;
	*pstrut = strut;
}

static intmax_t		get_nbr(va_list ap, t_print strut)
{
	if (strut.specs.z)
                return (va_arg(ap, size_t));
        if (strut.specs.lng > 1)
                return (va_arg(ap, unsigned long long));
        if (strut.specs.j)
                return (va_arg(ap, uintmax_t));
        if (strut.specs.lng == 1)
                return (va_arg(ap, unsigned long));
        if (strut.specs.shrt == 1)
                return ((unsigned short)va_arg(ap, unsigned int));
        if (strut.specs.shrt > 1)
                return ((unsigned char)va_arg(ap, unsigned int));
	return (va_arg(ap, unsigned int));
}

char				*get_udec(char f, t_print *pstrut, va_list ap)
{
	char			*trad;
	uintmax_t		nbr;

	if (f != 'u' && f != 'x' && f != 'X' && f != 'o')
		return (NULL);
	nbr = get_nbr(ap, *pstrut);
	if (f == 'u' || f == 'd')
		trad = my_uitoa(nbr);
	if (f == 'x' || f == 'X')
		trad = my_uitoa_base(nbr, "0123456789abcdef");
	if (f == 'X')
		trad = my_strtoupper(trad);
	if (f == 'o')
		trad = my_uitoa_base(nbr, "01234567");
	if (trad == NULL)
		return (NULL);
	cut_zero(&trad);
	fill_prefix(f, pstrut);
	(*pstrut).done = 1;
	return (trad);
}

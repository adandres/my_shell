/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   get_specifier.c                                 /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/28 18:38:10 by adandres               /    /  /         */
/*   Updated: 2020/04/02 16:37:25 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

static char		*get_string(char f, t_print *pstrut, va_list ap)
{
	char	*trad;

	if (f != 's' && f != 'c')
		return (NULL);
	if ((*pstrut).specs.lng == 1)
		return (NULL);
	if (f == 's')
		trad = my_strdup(va_arg(ap, char*));
	else
	{
		trad = (char*)malloc(sizeof(char) * 2);
		trad[0] = va_arg(ap, int);
		trad[1] = '\0';
	}
	(*pstrut).done = 1;
	return (trad);
}

static char		*get_wchar(char f, t_print *pstrut, va_list ap)
{
	wchar_t		*arg;
	char		*trad;

	if (f != 'S' && f != 's' && f != 'c' && f != 'C')
		return (NULL);
	if (f != 'S' && f != 'C' && (*pstrut).specs.lng != 1)
		return (NULL);
	(*pstrut).spe_put = 1;
	if (f != 'C' && f != 'c')
	{
		arg = va_arg(ap, wchar_t*);
		trad = (char*)arg;
	}
	else
	{
		arg = (wchar_t*)malloc(sizeof(wchar_t) * 2);
		arg[0] = va_arg(ap, wint_t);
		arg[1] = '\0';
		trad = (char*)arg;
		(*pstrut).spe_put++;
	}
	(*pstrut).done = 1;
	return (trad);
}

char		*get_specifier(char f, t_print *pstrut, va_list ap)
{
	char	*trad;
	int	index;
	char	*(*search[5])(char, t_print*, va_list) = {&get_dec, &get_udec, \
					&get_string, &get_addr, &get_wchar};

	index = 0;
	while (index < 5 && (*pstrut).done == 0)
		trad = search[index++](f, pstrut, ap);
	if ((*pstrut).done == 0)
		return (NULL);
	return (trad);
}

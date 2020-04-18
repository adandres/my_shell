/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   print_format.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/25 13:30:17 by adandres               /    /  /         */
/*   Updated: 2020/04/02 16:39:27 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

static void	put_wchar(wint_t c)
{
	write(1, &c, 1);
}

static void	spe_put(wchar_t *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		put_wchar(str[i]);
		i++;
	}
}

static void	print_char(char c, int n)
{
	int i;

	i = 0;
	if (n <= 0)
		return;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

static void	print_preffix(int preffix)
{
	if (preffix == 1)
		write(1, "0x", 2);
	if (preffix == 2)
		write(1, "0X", 2);
	if (preffix == 3)
		write(1, "0", 1);
}

static int		calc_width(t_print strut, int len)
{
	return (strut.flags.width - len - strut.padding.fp - strut.options.is_preffix);
}

static void		fill_padding(char *trad, t_print *pstrut)
{
	t_print strut;
	int	len;

	strut = *pstrut;
	if (trad == NULL)
		len = 1;
	else
		len = my_strlen(trad) - strut.options.is_neg;
	if (strut.flags.prec && (strut.options.is_number || strut.options.is_not_dec))
		strut.padding.fp = strut.flags.prec - len;
	if (strut.flags.width)
		strut.padding.fw = calc_width(strut, len);
	if (!(strut.flags.is_smin) && !(strut.flags.is_zero))
		strut.padding.nw = 1;
	*pstrut = strut;
}

static void		print_padding(t_print strut)
{
	char	c;

	if (strut.padding.nw)
		print_char(' ', strut.padding.fw);
	c = strut.options.preffix;
	if (strut.options.is_preffix)
		write(1, &c, 1);
	if (strut.options.is_not_dec || !(strut.padding.nw))
		print_preffix(strut.options.nd_prefix);
	if (strut.flags.is_zero)
		print_char('0', strut.padding.fw);
	if (strut.options.is_number || strut.options.is_not_dec)
		print_char('0', strut.padding.fp);
}

int		print_format(const char *format, va_list ap)
{
	t_print strut;
	char	*trad;

	strut = init_print();
	parse_padding(format, ap, &strut);
	parse_lenght(format, &strut);
	trad = get_specifier(format[strut.index], &strut, ap);
	fill_padding(trad, &strut);
	print_padding(strut);
	if (trad == NULL)
	{
		my_putchar(format[strut.index]);
		return (strut.index + 1);
	}
	if (strut.spe_put)
		spe_put((wchar_t*)trad);
	else
		my_putstr(trad + strut.options.is_neg);
	if (strut.flags.is_smin)
		print_char(' ', strut.padding.fw);
	if (strut.spe_put != 1)
		free(trad);
	return (strut.index + 1);
}

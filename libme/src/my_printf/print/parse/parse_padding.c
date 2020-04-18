/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   parse_padding.c                                 /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/22 19:53:05 by adandres               /    /  /         */
/*   Updated: 2020/03/31 17:13:26 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

static void		search_zero(const char *format, t_flag *pflags)
{
	t_flag	flags;
	int	i;

	i = 0;
	flags = *pflags;
	flags.step += 1;
	while (format[i] == '0')
	{
		flags.is_zero = 1;
		i++;
	}
	flags.onward += i;
	*pflags = flags;
}

static void		search_smin(const char *format, t_flag *pflags)
{
	t_flag	flags;
	int	i;

	i = 0;
	flags = *pflags;
	flags.step += 1;
	while (format[i] == '-')
	{
		flags.is_smin = 1;
		flags.step = 0;
		i++;
	}
	flags.onward += i;
	*pflags = flags;
}

static void		search_splus(const char *format, t_flag *pflags)
{
	t_flag	flags;
	int	i;

	i = 0;
	flags = *pflags;
	flags.step += 1;
	while (format[i] == '+')
	{
		flags.is_splus = 1;
		flags.step = 0;
		i++;
	}
	flags.onward += i;
	*pflags = flags;
}

static void		search_htag(const char *format, t_flag *pflags)
{
	t_flag	flags;
	int	i;

	i = 0;
	flags = *pflags;
	flags.step += 1;
	while (format[i] == '#')
	{
		flags.is_htag = 1;
		flags.step = 0;
		i++;
	}
	flags.onward += i;
	*pflags = flags;
}

static void		search_space(const char *format, t_flag *pflags)
{
	t_flag	flags;
	int	i;

	i = 0;
	flags = *pflags;
	flags.step += 1;
	while (format[i] == ' ')
	{
		flags.is_space = 1;
		flags.step = 0;
		i++;
	}
	flags.onward += i;
	*pflags = flags;
}

static int		get_nb(const char *format, int *pnb, va_list ap)
{
	int	i;

	i = 0;
	if (format[i] == '*')
	{
		*pnb = va_arg(ap, int);
		i++;
	}
	else if (my_isdigit(format[i]))
	{
		*pnb = my_atoi(format + i);
		while (my_isdigit(format[i]))
			i++;
	}
	return (i);
}

static int		search_wp(const char *format, va_list ap, t_flag *pflags)
{
	t_flag	flags;
	int	i;
	int	is_prec;
	int	nb;

	flags = *pflags;
	is_prec = 0;
	i = 0;
	nb = 0;
	if (format[i] == '.')
	{
		is_prec = 1;
		flags.is_zero = 0;
		i++;
	}
	i += get_nb(format + i, &nb, ap);
	if (i == 0)
		return (0);
	if (is_prec)
		flags.prec = nb;
	else
		flags.width = nb;
	flags.onward += i;
	*pflags = flags;
	return (1);
}

void		parse_padding(const char *format, va_list ap, t_print *pstrut)
{
	void	(*search_func[5])(const char *, t_flag*) = {&search_zero, &search_space, &search_smin, &search_splus, &search_htag};
	t_flag	flags;
	t_print strut;

	strut = *pstrut;
	flags = strut.flags;
	while (flags.step < 5)
	{
		search_func[flags.step](format + flags.onward, &flags);
		if (search_wp(format + flags.onward, ap, &flags))
			flags.step = 0;
	}
	strut.flags = flags;
	strut.index = flags.onward;
	*pstrut = strut;
}

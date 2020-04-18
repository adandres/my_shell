/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   parse_lenght.c                                  /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/30 16:44:56 by adandres               /    /  /         */
/*   Updated: 2020/03/30 16:46:12 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

static int		parse_lng(const char *format, t_print *pstrut)
{
	int i;
	t_print strut;

	i = 0;
	strut = *pstrut;
	if (format[i] != 'l')
		return (0);
	while (format[i] == 'l')
	{
		i++;
		strut.specs.lng++;
	}
	strut.index += i;
	*pstrut = strut;
	return (1);
}

static int		parse_shrt(const char *format, t_print *pstrut)
{
	int i;
	t_print strut;

	i = 0;
	strut = *pstrut;
	if (format[i] != 'h')
		return (0);
	while (format[i] == 'h')
	{
		i++;
		strut.specs.shrt++;
	}
	strut.index += i;
	*pstrut = strut;
	return (1);
}

static int		parse_z(const char *format, t_print *pstrut)
{
	int	i;

	i = 0;
	if (format[i] != 'z')
		return (0);
	(*pstrut).specs.z = 1;
	(*pstrut).index++;
	return (1);
}

static int		parse_j(const char *format, t_print *pstrut)
{
	int	i;

	i = 0;
	if (format[i] != 'j')
		return (0);
	(*pstrut).specs.j = 1;
	(*pstrut).index++;
	return (1);
}


void		parse_lenght(const char *format, t_print *pstrut)
{
	int	index;
	int	(*parse[4])(const char*, t_print*) = {&parse_lng, &parse_shrt,
		&parse_z, &parse_j};

	index = 0;
	while (index < 4)
	{
		if (parse[index](format + (*pstrut).index, pstrut))
			index = 0;
		else
			index++;
	}
}

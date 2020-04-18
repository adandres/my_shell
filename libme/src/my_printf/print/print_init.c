/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   print_init.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/25 13:59:50 by adandres               /    /  /         */
/*   Updated: 2020/03/30 16:58:42 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

static t_flag		init_flag(void)
{
	t_flag		flags;

	flags.is_htag = 0;
	flags.is_smin = 0;
	flags.is_space = 0;
	flags.is_splus = 0;
	flags.is_zero = 0;
	flags.onward = 0;
	flags.step = 0;
	flags.width = 0;
	flags.prec = 0;
	return (flags);
}

static t_padd		init_padd(void)
{
	t_padd padding;

	padding.fw = 0;
	padding.fp = 0;
	padding.nw = 0;
	return (padding);
}

static t_opt		init_opt(void)
{
	t_opt	options;

	options.is_number = 0;
	options.is_neg = 0;
	options.is_not_dec = 0;
	options.nd_prefix = 0;
	options.preffix = 0;
	options.is_preffix = 0;
	return (options);
}

static t_spec		init_spec(void)
{
	t_spec	specs;

	specs.lng = 0;
	specs.shrt = 0;
	specs.z = 0;
	specs.j = 0;
	return (specs);
}

t_print			init_print(void)
{
	t_print	strut;

	strut.flags = init_flag();
	strut.padding = init_padd();
	strut.options = init_opt();
	strut.specs = init_spec();
	strut.index = 0;
	strut.done = 0;
	strut.spe_put = 0;
	return (strut);
}

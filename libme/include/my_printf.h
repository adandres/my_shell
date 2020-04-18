/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_printf.h                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/18 12:07:35 by adandres               /    /  /         */
/*   Updated: 2020/04/02 16:34:47 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_PRINTF_H
# define MY_PRINTF_H

# include "libme.h"
# include <stdarg.h>
# include <stdio.h>
# include <wchar.h>
# include <stdint.h>

typedef struct  s_flag
{
	int     is_zero;
	int     is_smin;
	int     is_splus;
	int     is_htag;
	int     is_space;
	int     onward;
	int     step;
	int     width;
	int     prec;
}               t_flag;

typedef struct	s_opt
{
	int     is_number;
	int	is_neg;
	int     is_not_dec;
	int	nd_prefix;
	int     preffix;
	int     is_preffix;
}		t_opt;

typedef struct	s_padd
{
	int	fw;
	int	fp;
	int	nw;
}		t_padd;

typedef struct s_spec
{
	int	lng;
	int	shrt;
	int	z;
	int	j;
}		t_spec;

typedef struct	s_print
{
	struct s_flag	flags;
	struct s_padd	padding;
	struct s_opt	options;
	struct s_spec	specs;
	int		index;
	int		done;
	int		spe_put;
}		t_print;

int		my_printf(const char * restrict format, ...);

int             print_format(const char *format, va_list ap);
t_print		init_print(void);
void		parse_padding(const char *format, va_list ap, t_print *pstrut);
int		get_lenght(t_print strut);
char            *get_specifier(char f, t_print *pstrut, va_list ap);
char		*get_dec(char f, t_print *pstrut, va_list ap);
char		*get_udec(char f, t_print *pstrut, va_list ap);
char		*get_addr(char f, t_print *pstrut, va_list ap);
void		parse_lenght(const char *format, t_print *pstrut);

void		cut_zero(char **ptr);

#endif

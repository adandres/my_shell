/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   apply_term.c                                    /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/05/26 23:07:26 by adandres               /    /  /         */
/*   Updated: 2020/05/26 23:07:44 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static t_term	init_term(t_term term)
{
	if (tcgetattr(0, &term) == -1)
	{
		dprintf(2, "error tecgedwed\n");
		return (term);
	}
	return (term);
}

static t_term	canon_input(t_term term)
{
	term.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		dprintf(2, "failed to put in raw mode\n");
	return (term);
}

static t_term	reset_term(t_term backup)
{
	if (tcsetattr(0, 0, &backup) == -1)
		dprintf(2, "reset failed\n");
	my_putstr(SHOW_CURSOR);
	return (backup);
}

void	apply_term(char *op)
{
	static t_term	term;
	static t_term	term_backup;

	if (my_strequ(op, "INIT"))
	{
		term = init_term(term);
		term_backup = init_term(term_backup);
	}
	else if (my_strequ(op, "ROW"))
		term = canon_input(term);
	else if (my_strequ(op, "RESET"))
		term = reset_term(term_backup);
}

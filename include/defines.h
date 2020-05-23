/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   defines.h                                       /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/04/06 17:23:42 by adandres               /    /  /         */
/*   Updated: 2020/05/19 20:23:16 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define ARROW_UP		"\033[A"
# define ARROW_LEFT		"\033[D"
# define ARROW_DOWN		"\033[B"
# define ARROW_RIGHT		"\033[C"
# define HIDE_CURSOR	"\033[?25l"
# define SHOW_CURSOR	"\033[?25h"


/*
 ** Boolean
 */
# define TRUE		1
# define FALSE		0
# define SUCCESS	0
# define FAILURE	1

/*
 ** 	MAIN machine's states
 */
# define READ		0
# define PARSE		1
# define BUILD		2
# define EXEC		3
# define END		4
# define ERROR		5

# define EXIT       0
# define BECHO      1
# define CD         2
# define ENV        3
# define UNSET      4
# define SET        5
# define EXPORT     6

/*
 ** 	PARSE state machine's states
 */
# define SEMI		0
# define LOGIC		1
//# define PI		2
# define PIPE		20
# define REDIR		3
# define COMMAND	4
# define L_AND		10
# define L_OR		11
# define R_OUT		31
# define RA_OUT		32
# define R_IN		33
# define R_DOC		34
# define R_ER		35
# define R_RW		36
# define R_CP		37
# define R_ICL		38
# define R_OCL		39
# define WORD		40
# define CMD		41
# define BUILT		42
# define ARG		43
# define FILENAME	44
# define VAR		45
//# define PIPE		40
# define NUL		9

/*
 ** Here are the possible errors
 */

# define CUSTOM_ERROR	-1
# define NO_FOUND	1
# define NO_MEM		2
# define ERR_FORK	3
# define ERR_EXECVE	4
# define ERR_READ	5

/*
 **cd options
 */
# define P	1
# define L	2
# define HYPHEN 3

/*
 ** change struct termios to something smaller
 */
typedef struct termios	t_term;

/*
 ** define termcaps key
 */
# define ARROW_UP	"\033[A"
# define ARROW_LEFT	"\033[D"
# define ARROW_DOWN	"\033[B"
# define ARROW_RIGHT	"\033[C"
# define DEL_PREV_CHAR	"\033[D\033[K"
# define CLEAR_SCREEN	"\r\033[0K\033[2J\033[1;1H"
# define RESET_LINE	"\r\033[0K"
# define DEL_TO_ENDL	"\033[0J"
# define SAVE_CURSOR	"\0337"
# define RESTORE_CURSOR "\0338"

/*
 ** define termcaps values
 */
# define DEL			127
# define REV_DEL		51
# define ESC			27
# define CLEAR			12
# define TAB			9
# define RIGHT_ARROW	'C'
# define DOWN_ARROW		'B'
# define UP_ARROW		'A'
# define LEFT_ARROW		'D'
# define EOT			4

/*
 ** define ft_env options
 */
# define I_OPT 1
# define V_OPT 2
# define P_OPT 4
# define S_OPT 8
# define U_OPT 16

/*
 ** define special chars
 */
# define GREEN_ARROW	"{B_green}\u279C  {eoc}{cyan}"
# define RED_ARROW	"{B_red}\u279C  {eoc}{cyan}"
# define GUILLEMET	"{eoc}{B_gray} \u00BB {eoc}"

#endif

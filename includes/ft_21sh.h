/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 10:32:03 by lportay           #+#    #+#             */
/*   Updated: 2018/02/22 18:09:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include "ft_dlst.h"
# include "stack.h"
# include "ft_list.h"
# include "ft_string.h"
# include "ft_stdio.h"
# include "qbuf.h"
# include "ft_astr.h"
# include "ft_ctype.h"
# include "ft_hashset.h"
# include "kvp.h"
# include "builtins.h"
# include "expand.h"

# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <fcntl.h>
# include <time.h>
# include <limits.h>
# include <pwd.h>

# include "line.h"
# include "prompt.h"
# include "history.h"
# include "token.h"
# include "parser.h"
# include "exec.h"

# define NOMEM_STR				"No memory available for dynamic allocation\n"
# define NODIR_STR				"Error retrieving current directory\n"
# define FAILREAD_STR			"Can't read from STDIN\n"
# define BADQUOTES_STR			"Unexpected end of file\n"
# define FAILSETSIGHDLR_STR		"Couldn't set properly signal handlers.\n"

# define AMBIG_REDIR			"ambiguous redirect\n"

# define PATH					"/usr/local/bin/:/usr/bin:/bin"

//TO DELETE
# define DEBUG 		write(STDOUT_FILENO, "DEBUG\n", 6)
# define DEBUG1 	write(STDOUT_FILENO, "DEBUG1\n", 7)
# define DEBUG2 	write(STDOUT_FILENO, "DEBUG2\n", 7)
# define ERROR 		write(STDOUT_FILENO, "ERROR\n", 6)

typedef struct s_ctx	t_ctx;

enum					e_errcode
{
	SUCCESS,
	NOENVIRON,
	FAILREAD,
	NODIR,
	NOMEM,
	BADQUOTES,
	FAILSETSIGHDLR,
};

/*
** sizeof struct termios = 60
*/

//padder correctement la struct

struct					s_ctx
{
	/*
	**	JOB CONTROL - Might miss a lot of variables
	*/

	pid_t				pid;
	pid_t				pgid;
	int					fd;
	int	                istty;
	char				**path;
	t_list				*running_processes;

	/*
	**	EXECUTION HASH (for HASH builtin)
	*/

	t_hdict			*hash;
	t_hdict			*builtins;

	/*
	**	SHELL VARIABLES
	*/

	char				**environ;
	char				**locals;
	unsigned short		set;

	/*
	**	LINE EDITION
	*/

	t_line				line;
	t_hist				hist;
	t_line				*cur_line;//line currently modified
	char                *heredoc_eof;//current EOF
	char				prompt_mode[4];

	/*
	**	SHOPT BOOLS
	*/

	int					emacs_mode;
	int	                line_edition;
	int	                history;
	int					job_control;

	/*
	**	TERMINAL CONTEXT
	*/

	struct s_termcaps	tc;
	struct winsize		ws;
	struct termios		tios;
	struct termios		oldtios;
	char				**av;

	/*
	**	TBD
	*/

	t_token				*toklist; // Do we keep it here?
};


/*
typedef struct			s_typefunc
{
	int type;
	void	(*f)(void *ptr);
}
*/

void					vingtetunsh(char **av, char **environ);

int						init(t_ctx *ctx, char **av, char **environ);
t_hdict				*getbuiltins(void);
void					init_termcaps(t_ctx *ctx);
void					complete_environ(char ***environ);
int						create_locals(char ***locals);
char					**getpath(char **environ);


void					dump_err(char errcode);
void					fatal_err(char errcode, t_ctx *ctx);
void					wrap_exit(int status, t_ctx *ctx);

void					on_emem(int status);
void					max(size_t *a, size_t b);

int						set_sighandler(void);
t_ctx					*get_ctxaddr(t_ctx *ctxaddr);

/*
** Tools
*/

int						ft_putchar_stdin(int c);
bool					str_isblank(char *str);
bool					dlst_isblank(t_dlist *dlst);
bool					is_number(char *str);
bool					is_number_w_dash(char *str);

t_job					*parse(t_token *tok);
int						exec(t_job *extree);

// Shell script stuff

//enum	e_rword
//{
//		BANG,
//		LBRACE,
//		RBRACE,
//		CASE,
//		DO,
//		DONE,
//		ELIF,
//		ELSE,
//		ESAC,
//		FI,
//		FOR,
//		IF,
//		IN,
//		THEN,
//		UNTIL,
//		WHILE,
//};

/*
**	BUILTINS
*/

#endif

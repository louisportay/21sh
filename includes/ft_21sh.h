/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 10:32:03 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 17:39:27 by lportay          ###   ########.fr       */
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
# include "job_control.h"


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

# define NOMEM_STR				"Cannot allocate memory\n"
# define NODIR_STR				"error retrieving current directory\n"
# define FAILREAD_STR			"closing standard input\n"
# define BADQUOTES_STR			"unexpected end of file\n"
# define BADOPT_C_STR			"21sh: -c: option requires an argument\n"
# define BADOPT_F_STR			"21sh: -f: option requires an argument\n"

# define HELP1 "21sh, by vbastion and lportay:\n\n-h:\t\tDisplay this help\n"
# define HELP2 "-f <file>:\tRead <file>\n-c <cmd>:"
# define HELP3 "\tExecute <cmd>\n\n--rawline:\tdisable advanced line edition\n"
# define HELP4 "--norc:\t\tdo not read configuration file\n--nohist:\t"
# define HELP5 "disable command history\n"

# define AMBIG_REDIR			"ambiguous redirect\n"

# define PATH					"/usr/local/bin/:/usr/bin:/bin"

//TO DELETE
# define DEBUG 		write(STDOUT_FILENO, "DEBUG\n", 6)

# define DFL_BGCNT 8

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
	BADOPT_C,
	BADOPT_F,
};

/*
** sizeof struct termios = 60
*/

/*
** padder correctement la struct
*/

struct					s_ctx
{

	/*
	**	JOB CONTROL - Might miss a lot of variables
	*/

	pid_t				pid;
	pid_t				pgid;
	int					fd;
	int					istty;
	char				**path;
	t_job				**bg_jobs;
	size_t				bg_cnt;
	t_job				*fg_job;
	int					exe_stack;
	t_list				*bgs;

	/*
	**	EXECUTION HASH (for HASH builtin)
	*/

	t_hdict				*hash;
	t_hdict				*builtins;

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
	t_line				*cur_line;
	char				prompt_mode[4];
	int					ret_tcget;
	int					tty;

	/*
	**	SHOPT BOOLS
	*/

	int					emacs_mode;
	int					line_edition;
	int					config_file;
	int					history;
	int					job_control;

	/*
	**	TERMINAL CONTEXT
	*/

	struct s_termcaps	tc;
	struct winsize		ws;
	struct termios		tios;
	struct termios		oldtios;
	char				**av;

};

void					vingtetunsh(char **av, char **environ);

void					exec_pipe(t_dlist *input);
int						init(t_ctx *ctx, char **av, char **environ);
t_hdict					*getbuiltins(void);
void					init_termcaps(t_ctx *ctx);
void					get_shell_opt(t_ctx *ctx, char **av);
void					complete_environ(char ***environ);
int						create_locals(char ***locals);
char					**getpath(char **environ);

void					dump_err(char errcode);
void					fatal_err(char errcode, t_ctx *ctx);
void					wrap_exit(int status, t_ctx *ctx);

void					on_emem(int status);
void					max(size_t *a, size_t b);

int						set_sighandler(void);
t_ctx					*get_ctxaddr(void);

/*
** Tools
*/

int						ft_putchar_stdin(int c);
bool					str_isblank(char *str);
bool					dlst_isblank(t_dlist *dlst);
bool					is_number(char *str);
bool					is_number_w_dash(char *str);

t_job					*parse(t_token *tok);
int						job_waitforit(t_job *j, t_ctx *ctx);

void					sighandler(int signo);

void					ft_assert(void ***arr, size_t len);

/*
**	Shell script stuff
**
**	enum	e_rword
**	{
**		BANG,
**		LBRACE,
**		RBRACE,
**		CASE,
**		DO,
**		DONE,
**		ELIF,
**		ELSE,
**		ESAC,
**		FI,
**		FOR,
**		IF,
**		IN,
**		THEN,
**		UNTIL,
**		WHILE,
**	};
*/

#endif

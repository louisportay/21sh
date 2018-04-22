/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:44:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/22 13:25:04 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H

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
# include "ft_printf.h"
# include "bridge.h"

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
# include <dirent.h>

# include "line.h"
# include "prompt.h"
# include "history.h"
# include "token.h"
# include "parser.h"
# include "exec.h"
# include "autocomplete.h"

# define NOMEM_STR		"42sh: Cannot allocate memory\n"
# define NODIR_STR		"42sh: error retrieving current directory\n"
# define FAILREAD_STR	"42sh: closing standard input\n"
# define BADQUOTES_STR	"42sh: unexpected end of file\n"
# define BADOPT_C_STR	"42sh: -c: option requires an argument\n"
# define CTX_ERR_STR	"42sh: context error\n"
# define NOPROC_STR		"42sh: setpgid: No such process\n"
# define EFILEDESC_STR	"42sh: Too much file descriptor\n"
# define WAITINTR_STR	"42sh: waitpid: interrupted by a caught signal\n"
# define WAITCTX_STR	"42sh: waitpid: context error\n"

# define HELP1 "42sh, by vbastion and lportay:\n\n-h:\t\tDisplay this help\n"
# define HELP2 "-c <cmd>:"
# define HELP3 "\tExecute <cmd>\n\n--rawline:\tdisable advanced line edition\n"

# define TERM_FD_STDIN	10
# define TERM_FD_STDOUT	11
# define TERM_FD_STDERR	12
# define TERM_FD		13
# define TERM_FD_TTY	14

/*
** # define HELP4 "--norc:\t\tdo not read configuration file\n"
*/

# define PATH					"/usr/local/bin/:/usr/bin:/bin"

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
	CTX_ERR,
	NOPROC,
	EFILEDESC,
	EWAITINTR,
	EWAITCTX
};

/*
** sizeof struct termios = 60
*/

/*
** padder correctement la struct
*/

struct					s_ctx
{
	pid_t				pid;
	int					term_fd;
	int					std_fd[3];
	int					istty;
	char				**path;

	t_hdict				*hash;
	t_hdict				*builtins;

	char				**environ;
	char				**locals;
	unsigned short		set;

	t_line				line;
	t_hist				hist;
	t_line				*cur_line;
	t_dlist				*yank;
	char				prompt_mode[4];
	int					ret_tcget;

	int					emacs_mode;
	int					line_edition;
	int					config_file;
	int					history;
	int					job_control;

	struct s_termcaps	tc;
	struct winsize		ws;
	struct termios		tios;
	struct termios		oldtios;
	char				**av;

	char				last_ret;
	char				*last_argv;
};

void					vingtetunsh(char **av, char **environ);

void					exec_loop(t_dlist *input);
int						init(t_ctx *ctx, char **av, char **environ);
void					init_ctx(t_ctx *ctx, char **av, char **environ);
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

void					set_sighandler(void);
t_ctx					*get_ctxaddr(void);

/*
** Tools
*/

int						ft_putchar_stdin(int c);
bool					str_isblank(char *str);
bool					dlst_isblank(t_dlist *dlst);
bool					is_number(char *str);
bool					is_number_w_dash(char *str);

void					sighandler(int signo);

void					ft_assert(void ***arr, size_t len);

void					path_reset(t_ctx *ctx, int regen);

void					sighand_int(int signo);

size_t					ft_read(int fd, char *buffer, size_t size);

int						print_err(char *msg, int fd);

char					*env_path_get(char *exe, char **pathes);

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

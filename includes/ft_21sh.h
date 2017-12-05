/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 10:32:03 by lportay           #+#    #+#             */
/*   Updated: 2017/12/05 12:10:24 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_SH21_H

# include "libft.h"
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <fcntl.h>

# define NOENVIRON_STR	"Invalid Environment to use with this program.\n"
# define NOWINDOW_STR	"Couldn't retrieve window attributes.\n"
# define FAILSETENV_STR "Couldn't set properly the Environment.\n"
# define FAILSETLOCAL_STR "Couldn't set properly Local Variables.\n"
# define FAILSETSIGHDLR_STR "Couldn't set properly Sighandlers.\n"
# define FAILREAD_STR	"Can't read from STDIN\n"

# define NODIR_STR		"Error retrieving current directory\n"
# define NOMEM_STR		"Not enough memory available for dynamic allocation\n"

#define HISTSIZE "10"
#define HISTFILESIZE "10"
#define HISTFILE ".21sh_history"

# define T_HISTENTRY(ptr)	((t_histentry *)ptr)

# define DEBUG 	write(STDOUT_FILENO, "DEBUG\n", 6)


enum				e_errcode
{
	SUCCESS,
	NOENVIRON,
	NOWINDOW,
	FAILSETENV,
	FAILSETLOCAL,
	FAILSETSIGHDLR,
	FAILREAD,
	NODIR,
	NOMEM,
};

enum		e_readcode
{
	READON,
	READERROR,
	FINISHREAD,
	EXITSHELL,
};

struct		s_termcaps
{
	char	*le;
	char	*nd;
	char	*im;
	char	*ei;
	char	*dc;
};

typedef struct		s_error
{
	int 			errno;
	char 			*errmessage;
}					t_error;

typedef struct			s_histentry
{
	t_dlist		*line;
	unsigned	index;
}						t_histentry;

/*
** struct termios = 60 bytes
** struct winsize = 8 bytes
*/

typedef struct			s_21sh
{
	t_hash 				*localvar[HASHSIZE];
	struct termios		tios;
	struct termios		oldtios;
	struct s_termcaps	tc;
	struct winsize		ws;
	t_dlist				*line;
	t_dlist				*histlist;
	int					histindex;
	char				**environ;
	int					histfile;
	bool				line_edition;
	bool				history;

}						t_21sh;

/* histlist --> HEAD
**   			histentry --> line	--> HEAD
**				...					--> l
**									--> s
**									--> ' '
**									--> -
**									--> l
**									--> ...
**							--> index
**				dlist
** dlist		(histentry)
*/
void	vingtetunsh(char **env);

void	fatal_err(char errcode, t_21sh *env);
void	wrap_exit(int status, t_21sh *env);

int		wrap_signal(void);
void	sig_switch(int signum, t_21sh *env);

void		init_hist(t_21sh *env);
int			get_histfile(t_21sh *env);
void		del_history(t_dlist	**history);
t_histentry	*new_histentry(t_dlist *line, unsigned index);
void		dump_history(t_dlist *histlist);
void		trim_history(t_dlist **histlist, t_hash *histsizebucket);
void		save_history(t_hash **localvar, t_dlist *histlist);

void 	lineread(t_21sh *env);
void	getrawline(t_21sh *env);

void	print_prompt(t_21sh *env);

int		ft_putchar_stdin(int c);

void	del_histentry(void *histentry, size_t histentrysize);

enum	e_toktype
{
		WORD,
		IO_NUMBER,
		NEWLINE,
		PIPE,
		DPIPE,
		AND,
		LAND,
		OR,
		LOR,
		SEMICOL,
		DSEMICOL,
		BSLASH,
		LREDIR,
		RSREDIR,
		HEREDOC,
		RDREDIR
};

typedef struct		s_token
{
	t_dlist 		*first_letter;
	t_dlist 		*last_letter;
	struct s_token	*next_tok;
	enum e_toktype	type;
}					t_token;

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

#endif

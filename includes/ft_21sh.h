/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 10:32:03 by lportay           #+#    #+#             */
/*   Updated: 2017/12/14 10:09:35 by lportay          ###   ########.fr       */
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
# include <time.h>
# include <limits.h>
# include <pwd.h>

# define NOENVIRON_STR	"Invalid Environment to use with this program.\n"
# define FAILSETSIGHDLR_STR "Couldn't set properly Sighandlers.\n"
# define FAILREAD_STR	"Can't read from STDIN\n"

# define NODIR_STR		"Error retrieving current directory\n"
# define NOMEM_STR		"Not enough memory available for dynamic allocation\n"

# define READBUF 6

# define EOT	4
# define DEL	127
# define RETURN	'\n'
# define C_B '\002'
# define C_F '\006'
# define C_L '\f'	// '\014'
# define C_N '\016'
# define C_O '\017'
# define C_P '\020'
# define C_R '\022'

# define ESC	"\033"

# define UP_KEY "\033[A"
# define DOWN_KEY "\033[B"
# define RIGHT_KEY "\033[C"
# define LEFT_KEY "\033[D"

# define C_UP "\E[1;5A"
# define C_DOWN "\E[1;5B"

# define PS1  "=\\s=$ "//"SUPERFUCKINGREALLYLONGPROMPT$ "
# define PS2 "> "
# define PS3 ""
# define PS4 "+ "

#define HISTSIZE "30"
#define HISTFILESIZE "20"
#define HISTFILE ".21sh_history"

/*
** This must be $(NAME) in the makefile
*/

# define SHELLNAME "21sh"

# define T_HISTENTRY(ptr)	((t_histentry *)ptr)

# define PROMPT_FLAG(FUNC, FLAG)	(t_prompt_flag){.func = FUNC, .flag = FLAG}
# define VAR(KEY, VAL)				(t_var){.key = KEY, .val = VAL}

# define DEBUG 		write(STDOUT_FILENO, "DEBUG\n", 7)
# define DEBUG1 	write(STDOUT_FILENO, "DEBUG1\n", 8)


enum				e_errcode
{
	SUCCESS,
	NOENVIRON,
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

//regrouper les termcaps logiquement

struct		s_termcaps
{
	char	*le;
	char	*nd;
	char	*im;
	char	*ei;
	char	*dc;
	char	*cr;
	char	*up;
	char	*dow;
	char	*cl;
	char	*cd;
//	char	*cm;
};

/*
** struct termios = 60 bytes
** struct winsize = 8 bytes
*/

//padder correctement

typedef struct			s_21sh
{
	t_hash 				*localvar[HASHSIZE];
	char				**environ;
	
	struct termios		tios;
	struct termios		oldtios;
	struct winsize		ws;

	struct s_termcaps	tc;
	t_dlist				*line;
	t_dlist				*lastline;
	t_dlist				*histlist;
	int					histindex;
	int					histfile;
	size_t				cursor_offset;	// number of lines by (cursor_offset / ws_col) col number by (cursor_offset % ws_col)
	size_t				line_len;		// include the prompt len
	unsigned			cursor_line;
	unsigned			num_lines;
	char 				prompt_mode;
	bool				multiline;
	bool				emacs_mode;

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

typedef struct	s_prompt_flag
{
	void		(*func)(t_21sh *env);
	char		flag;
}				t_prompt_flag;


typedef struct	s_var
{
	char *key;
	char *val;
}				t_var;

typedef struct			s_histentry
{
	t_dlist		*line;
	unsigned	index;
}						t_histentry;

void	vingtetunsh(char **av, char **env);

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
void		del_histentry(void *histentry, size_t histentrysize);

void	lineread(t_21sh *env);
void	getrawline(t_21sh *env);

void	clear_line(t_21sh *env);
void	redraw_line(t_21sh *env);

void	print_prompt(t_21sh *env);

int		ft_putchar_stdin(int c);
bool	isonlywhitespace(char *str);


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

#endif

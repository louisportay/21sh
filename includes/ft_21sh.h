/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 10:32:03 by lportay           #+#    #+#             */
/*   Updated: 2017/12/28 11:04:37 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

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
# define NOMEM_STR		"Not enough memory available for dynamic allocation\n"
# define NODIR_STR		"Error retrieving current directory\n"
# define FAILSETSIGHDLR_STR "Couldn't set properly signal handlers.\n"
# define FAILREAD_STR	"Can't read from STDIN\n"
# define BADQUOTES_STR		"Unexpected end of file\n"

# define READLEN 6

# define C_A '\001'
# define C_B '\002'
# define C_D '\004'
# define C_E '\005'
# define C_F '\006'
# define C_H '\b'	// '\008'
# define C_I '\t'	// '\011'
# define C_J '\n'	// '\012'
# define C_K '\v'	// '\013'
# define C_L '\f'	// '\014'
# define C_N '\016'
# define C_O '\017'
# define C_P '\020'
# define C_R '\022'
# define C_U '\025'
# define C_W '\027'
# define C_Y '\031'
# define ESC '\033'

# define NEWLINE_	'\n'
# define TAB		'\t'
# define BACKSPACE	127

# define M_B "\Eb"
# define M_D "\Ed"
# define M_E "\Ee"
# define M_F "\Ef"

//mettre des ifdef pour rendre les defines de keystroke portables entre linux et Apple

# define UP_KEY "\E[A"
# define DOWN_KEY "\E[B"
# define RIGHT_KEY "\E[C"
# define LEFT_KEY "\E[D"

# define END  "\E[F"//70 MAC
# define HOME "\E[H"//72 MAC
# define DELETE "\E[3~"//51 MAC
# define PAGE_UP "\E[5~" //MAC ?
# define PAGE_DOWN "\E[6~" //MAC ?

# define C_UP "\E[1;5A"
# define C_DOWN "\E[1;5B"
# define C_RIGHT "\E[1;5C"
# define C_LEFT "\E[1;5D"

# define C_END "\E[1;5F"
# define C_HOME "\E[1;5H"
# define C_DELETE "\E[3;5~"
# define C_PAGEUP "\E[5;5~"
# define C_PAGEDOWN "\E[6;5~"

# define PS1_VAL  "=\\s=$ "
# define PS2_VAL "> "
# define PS3_VAL ""
# define PS4_VAL "+ "

#define HISTSIZE "30"
#define HISTFILESIZE "30"
#define HISTFILE ".21sh_history"

#ifdef __linux__
# define CUSTOM_HOST_NAME_MAX HOST_NAME_MAX
#elif __APPLE__
# define CUSTOM_HOST_NAME_MAX _POSIX_HOST_NAME_MAX
#endif

/*
** This must be $(NAME) in the makefile
*/

# define SHELLNAME "21sh"

# define T_HISTENTRY(ptr)	((t_histentry *)ptr)

//TO DELETE
# define DEBUG 		write(STDOUT_FILENO, "DEBUG\n", 7)
# define DEBUG1 	write(STDOUT_FILENO, "DEBUG1\n", 8)
# define DEBUG2 	write(STDOUT_FILENO, "DEBUG2\n", 8)


enum				e_errcode
{
	SUCCESS,
	NOENVIRON,
	FAILSETSIGHDLR,
	FAILREAD,
	NODIR,
	NOMEM,
	BADQUOTES,
};

enum		e_readcode
{
	READON,
	READERROR,
	FINISHREAD,
	EXITSHELL,
	ERR_QUOTE,
};

enum		e_linestate
{
	UNQUOTED,	//0
	BSLASH,		//1
	SQUOTE,		//2
	DQUOTE,		//3
	BQUOTE,		//4
};

enum		e_prompt_mode
{
	NOPROMPT,
	PS1,
	PS2,
	PS3,
	PS4,
};

//regrouper les termcaps logiquement, dans le bon ordre

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
	char	*sc;
	char	*rc;
};

/*
** struct termios = 60 bytes
** struct winsize = 8 bytes
*/

//padder correctement
// faire des sous-structures en fonction des modules ? (demande beaucoup de refacto, utilise potentiellement plus de lignes)

typedef struct			s_21sh
{
	t_hash 				*localvar[HASHSIZE];
	char				**environ;
	
	struct termios		tios;
	struct termios		oldtios;
	struct winsize		ws;

	struct s_termcaps	tc;

	t_dlist				*line;
	t_dlist				*yank;
	t_dlist				*lastline;
	t_dlist				*histlist;
	t_dlist				*split_line;
	int					histindex;
	int					histfile;
	size_t				cursor_offset;	// number of lines by (cursor_offset / ws_col) col number by (cursor_offset % ws_col)
	size_t				line_len;		// include the prompt len
	t_stack				*linestate;
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

# define PROMPT_FLAG(FUNC, FLAG)	(t_prompt_flag){.func = FUNC, .flag = FLAG}
# define VAR(KEY, VAL)				(t_var){.key = KEY, .val = VAL}
# define LINE_FUNC(TEST, FUNC)		(t_line_func){.test = TEST, .f = FUNC}

typedef struct	s_prompt_flag
{
	void		(*func)(t_21sh *env);
	char		flag;
}				t_prompt_flag;

typedef struct	s_line_func
{
	bool	(*test)(t_21sh *env, char *buf, int *bufindex);
	void	(*f)(t_21sh *env);
}				t_line_func;

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

void	dump_err(char errcode);
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
void		add_histentry(t_21sh *env);

void	wrap_lineread(t_21sh *env);
void	lineread(t_21sh *env);
void	getrawline(t_21sh *env);

void	clear_line(t_21sh *env);
void	redraw_line(t_21sh *env);

void	print_prompt(t_21sh *env);

int		ft_putchar_stdin(int c);
bool	isonlywhitespace(char *str);
bool	dlst_isonlywhitespace(t_dlist *dlst);

void	move_cursor_n_columns(int n);
void	move_cursor_n_lines(int n);
void	move_cursor_forward(t_21sh *env);
void	move_cursor_backward(t_21sh *env);
void	move_cursor_end_of_line(t_21sh *env);

void	print_line_cursor_len(t_21sh *env, t_dlist *list);
void	print_line_cursor(t_21sh *env, t_dlist *list);
void	print_line(t_dlist *list);

void	up_key(t_21sh *env);
void	down_key(t_21sh *env);

void	insert_char(char *buf, t_21sh *env);
void	del_previous_char(t_21sh *env);
void	del_current_char(t_21sh *env);

void	kill_line_end(t_21sh *env);
void	kill_line_beginning(t_21sh *env);
void	kill_prev_word(t_21sh *env);
//void	kill_next_word(t_21sh *env);
void	yank(t_21sh *env);

void	redraw_line(t_21sh *env);
void	clear_line(t_21sh *env);
void	clear_screen_(t_21sh *env);

void	go_upper_line(t_21sh *env);
void	go_lower_line(t_21sh *env);
void	go_to_line_beginning(t_21sh *env);
void	go_to_line_end(t_21sh *env);
void	go_to_previous_word(t_21sh *env);
void	go_to_next_word(t_21sh *env);

void	load_line(t_21sh *env);
void	update_linemode(t_21sh *env);
void	lkey(t_21sh *env);
void	rkey(t_21sh *env);

void	reverse_emacs_mode(t_21sh *env);

bool	test_kill_beginline(t_21sh *env, char *buf, int *bufindex);
bool	test_kill_endline(t_21sh *env, char *buf, int *bufindex);
bool	test_clear_screen(t_21sh *env, char *buf, int *bufindex);
bool	test_yank(t_21sh *env, char *buf, int *bufindex);
bool	test_go_next_word(t_21sh *env, char *buf, int *bufindex);
bool	test_go_prev_word(t_21sh *env, char *buf, int *bufindex);
bool	test_upper_line(t_21sh *env, char *buf, int *bufindex);
bool	test_lower_line(t_21sh *env, char *buf, int *bufindex);
bool	test_line_end(t_21sh *env, char *buf, int *bufindex);
bool	test_line_beginning(t_21sh *env, char *buf, int *bufindex);
bool	test_upkey(t_21sh *env, char *buf, int *bufindex);
bool	test_downkey(t_21sh *env, char *buf, int *bufindex);
bool	test_rkey(t_21sh *env, char *buf, int *bufindex);
bool	test_lkey(t_21sh *env, char *buf, int *bufindex);
bool	test_del_current_char(t_21sh *env, char *buf, int *bufindex);
bool 	test_del_previous_char(t_21sh *env, char *buf, int *bufindex);
bool	test_emacs_mode(t_21sh *env, char *buf, int *bufindex);
bool	test_load_line(t_21sh *env, char *buf);

bool	test_killprevword(t_21sh *env, char *buf, int *bufindex);
//bool	test_killnextword(t_21sh *env, char *buf, int *bufindex);



/*enum	e_toktype
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
*/

#endif

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


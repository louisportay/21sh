/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:02:11 by lportay           #+#    #+#             */
/*   Updated: 2018/02/07 13:07:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# define C_A '\001'
# define C_B '\002'
# define C_D '\004'
# define C_E '\005'
# define C_F '\006'
# define C_H '\b'	// '\008'
# define C_I '\t'	// '\011'	//== TAB_INSERT Not implemented
# define C_J '\n'	// '\012'
# define C_K '\v'	// '\013'
# define C_L '\f'	// '\014'
# define C_N '\016'
# define C_O '\017'
# define C_P '\020'
# define C_R '\022' //Not Implemented
# define C_U '\025'
# define C_W '\027'
# define C_Y '\031'
# define ESC '\033'

# define NEWLINE_	'\n'
# define TAB		'\t'
# define BACKSPACE	127

# define M_B "\Eb"
# define M_D "\Ed"//Not implemented
# define M_E "\Ee"
# define M_F "\Ef"

//mettre des ifdef pour rendre les defines de keystroke portables entre Linux et Apple

# define UP_KEY "\E[A"
# define DOWN_KEY "\E[B"
# define RIGHT_KEY "\E[C"
# define LEFT_KEY "\E[D"

# define END  "\E[F"
# define HOME "\E[H"
# define DELETE "\E[3~"

#ifdef __linux__
# define C_UP "\E[1;5A"
#elif __APPLE__
#define C_UP "\E[5~"//Shift+PageUp
#endif

#ifdef __linux__
# define C_DOWN "\E[1;5B"
#elif __APPLE__
# define C_DOWN "\E[6~"//Shift+PageDown
#endif


# define C_RIGHT "\E[1;5C"
# define C_LEFT "\E[1;5D"

# define C_END "\E[1;5F"
# define C_HOME "\E[1;5H"
# define C_DELETE "\E[3;5~"
# define C_PAGEUP "\E[5;5~"
# define C_PAGEDOWN "\E[6;5~"

#define READLEN 6

typedef struct s_ctx	t_ctx;

enum					e_readcode
{
	READON,
	READERROR,
	FINISHREAD,
	EXITSHELL,
	ERR_QUOTE,
};

enum					e_linestate
{
	UNQUOTED,	
	BSLASH,		
	SQUOTE,		
	DQUOTE,		
//	BQUOTE,		42SH	
	PAREN,
	BRACE,
	BRACKET,
	HASH,
	HEREDOC,
};

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
** sizeof struct winsize = 8
*/

typedef struct			s_line
{
	t_dlist				*line;
	t_dlist				*yank;
	t_dlist				*lastline;
	t_dlist				*split_line;
	t_dlist				*final_newline;
	t_stack				*linestate;
	size_t				cursor_offset;	// number of lines by (cursor_offset / ws_col) col number by (cursor_offset % ws_col)
	size_t				line_len;		// include the prompt len
	unsigned			cursor_line;
	unsigned			num_lines;
	bool				multiline;
	bool				line_saved;
}						t_line;

typedef struct	s_key
{
	char		buf[READLEN];
	int			i;
}				t_key;

# define TEST_FUNC(TEST, FUNC)		(t_line_pair){.test = TEST, .func = FUNC}

typedef bool	(*t_line_test)(t_ctx *env, t_line *l, t_key *key);
typedef void	(*t_line_func)(t_ctx *env, t_line *l);

typedef struct	s_line_pair
{
	t_line_test	test;
	t_line_func func;
}				t_line_pair;

void	wrap_lineread(t_ctx *env, t_line *l, char *prompt_mode);
void	lineread(t_ctx *env, t_line *l);
void	getrawline(t_ctx *env, t_line *l);
int		user_input(t_ctx *env, t_line *l, t_key *key);

void	clear_line(t_ctx *env, t_line *l);
void	redraw_line(t_ctx *env, t_line *l);
void	clear_screen_(t_ctx *env, t_line *l);

void	move_cursor_n_columns(int n);
void	move_cursor_n_lines(int n);
void	move_cursor_forward(t_ctx *env, t_line *l);
void	move_cursor_backward(t_ctx *env, t_line *l);
void	move_cursor_end_of_line(t_ctx *env, t_line *l);

void	go_upper_line(t_ctx *env, t_line *l);
void	go_lower_line(t_ctx *env, t_line *l);
void	go_to_line_beginning(t_ctx *env, t_line *l);
void	go_to_line_end(t_ctx *env, t_line *l);
void	go_to_previous_word(t_ctx *env, t_line *l);
void	go_to_next_word(t_ctx *env, t_line *l);

void	print_line_cursor_len(t_line *l, t_dlist *list);
void	print_line_cursor(t_line *l, t_dlist *list);
void	print_line(t_dlist *list);

void	up_key(t_ctx *env, t_line *l);
void	down_key(t_ctx *env, t_line *l);
void	lkey(t_ctx *env, t_line *l);
void	rkey(t_ctx *env, t_line *l);

void	insert_char(char *buf, t_ctx *env, t_line *l);
void	del_previous_char(t_ctx *env, t_line *l);
void	del_current_char(t_ctx *env, t_line *l);

void	kill_line_end(t_ctx *env, t_line *l);
void	kill_line_beginning(t_ctx *env, t_line *l);
void	kill_prev_word(t_ctx *env, t_line *l);
//void	kill_next_word(t_ctx *env, t_line *l);
void	yank(t_ctx *env, t_line *l);

bool	test_kill_beginline(t_ctx *env, t_line *l, t_key *key);
bool	test_kill_endline(t_ctx *env, t_line *l, t_key *key);
bool	test_killprevword(t_ctx *env, t_line *l, t_key *key);
//bool	test_killnextword(t_ctx *env, t_line *l, t_key *key);
bool	test_clear_screen(t_ctx *env, t_line *l, t_key *key);
bool	test_yank(t_ctx *env, t_line *l, t_key *key);
bool	test_go_next_word(t_ctx *env, t_line *l, t_key *key);
bool	test_go_prev_word(t_ctx *env, t_line *l, t_key *key);
bool	test_upper_line(t_ctx *env, t_line *l, t_key *key);
bool	test_lower_line(t_ctx *env, t_line *l, t_key *key);
bool	test_line_end(t_ctx *env, t_line *l, t_key *key);
bool	test_line_beginning(t_ctx *env, t_line *l, t_key *key);
bool	test_upkey(t_ctx *env, t_line *l, t_key *key);
bool	test_downkey(t_ctx *env, t_line *l, t_key *key);
bool	test_rkey(t_ctx *env, t_line *l, t_key *key);
bool	test_lkey(t_ctx *env, t_line *l, t_key *key);
bool	test_del_current_char(t_ctx *env, t_line *l, t_key *key);
bool 	test_del_previous_char(t_ctx *env, t_line *l, t_key *key);
bool	test_emacs_mode(t_ctx *env, t_line *l, t_key *key);

bool	test_load_line(t_ctx *env, t_line *l, t_key *key);

void	load_line(t_ctx *env, t_line *l);
void	update_line(t_ctx *env, t_line *l);
void	update_linestate(t_stack **state, char c);
void	query_linestate(t_dlist *dlst, t_stack **linestate);
void	query_hdocstate(t_dlist *dlst, t_stack **linestate, char *eof);
void	reverse_emacs_mode(t_ctx *env, t_line *l);
void	join_split_lines(t_line *l);
void	err_quotes(t_line *l);


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:02:11 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 17:38:36 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

/*
** C_I + C_R are currently not implemented
*/

# define C_A		'\001'
# define C_B 		'\002'
# define C_C 		'\003'
# define C_D 		'\004'
# define C_E 		'\005'
# define C_F 		'\006'
# define C_H 		'\b'
# define C_I 		'\t'
# define C_J 		'\n'
# define C_K 		'\v'
# define C_L 		'\f'
# define C_N 		'\016'
# define C_O 		'\017'
# define C_P 		'\020'
# define C_R 		'\022'
# define C_U 		'\025'
# define C_W 		'\027'
# define C_Y 		'\031'
# define ESC 		'\033'
# define NL			'\n'
# define TAB		'\t'
# define BACKSPACE	127
# define M_B		"\Eb"
# define M_D 		"\Ed"
# define M_E 		"\Ee"
# define M_F 		"\Ef"
# define UP_KEY		"\E[A"
# define DOWN_KEY	"\E[B"
# define RIGHT_KEY	"\E[C"
# define LEFT_KEY	"\E[D"
# define END		"\E[F"
# define HOME		"\E[H"
# define DELETE		"\E[3~"
# define C_RIGHT "\E[1;5C"
# define C_LEFT "\E[1;5D"
# define C_END "\E[1;5F"
# define C_HOME "\E[1;5H"
# define C_DELETE "\E[3;5~"
# define C_PAGEUP "\E[5;5~"
# define C_PAGEDOWN "\E[6;5~"

/*
** Ctrl + UP_KEY on Linux
** Shift + PageUp on Mac OS
*/

# ifdef __linux__
#  define C_UP "\E[1;5A"
# elif __APPLE__
#  define C_UP "\E[5~"
# endif

/*
** Ctrl + DOWN_KEY on Linux
** Shift + PageDown on Mac OS
*/

# ifdef __linux__
#  define C_DOWN "\E[1;5B"
# elif __APPLE__
#  define C_DOWN "\E[6~"
# endif

/*
** Maximum numbers of characters in the read buffer at a single time
*/

# define READLEN 6

typedef struct s_ctx	t_ctx;

enum	e_readcode
{
	READON,
	READERROR,
	FINISHREAD,
	EXITSHELL,
	ERR_QUOTE,
};

struct			s_termcaps
{
	char		*le;
	char		*nd;
	char		*im;
	char		*ei;
	char		*dc;
	char		*cr;
	char		*up;
	char		*dow;
	char		*cl;
	char		*cd;
	char		*sc;
	char		*rc;
};

/*
** sizeof struct winsize = 8
**
**	cursor_line		:	Line on which the cursor is
**	num_lines		:	Total number of lines minus 1
**	offset_inline	:	Number of characters in front of the cursor in that
**		inline (space delimited by \n)
**  prompt_len		:	prompt len on the lastline (if it contains \n)
*/

/*
** # define INFO dprintf(dump_w, "=====================\n
** cursor_line = %u\nnum_lines = %u\noffset_inline = %u\nprompt_len = %u\n\n
** wincol = %u\nwinlin = %u\n", l->cursor_line, l->num_lines, l->offset_inline,
** l->prompt_len, ctx->ws.ws_col, ctx->ws.ws_row)
*/

typedef struct	s_line
{
	t_dlist		*line;
	t_dlist		*split_line;
	t_dlist		*yank;
	t_dlist		*lastline;
	t_stack		*linestate;
	unsigned	cursor_line;
	unsigned	num_lines;
	unsigned	offset_inline;
	unsigned	prompt_len;
	char		*eohdoc;
	bool		heredoc;
}				t_line;

typedef struct	s_key
{
	char		buf[READLEN];
	int			i;
}				t_key;

typedef bool	(*t_line_test)(t_ctx *env, t_line *l, t_key *key);
typedef void	(*t_line_func)(t_ctx *env, t_line *l);

typedef struct	s_line_pair
{
	t_line_test	test;
	t_line_func fun;
}				t_line_pair;

void			ft_readline(t_ctx *ctx, t_line *l, char *prompt_mode);
void			lineread(t_ctx *env, t_line *l);
void			getrawline(t_ctx *env, t_line *l);
int				user_input(t_ctx *env, t_line *l, t_key *key);

void			redraw_line(t_ctx *ctx, t_line *l);
void			clear_line(t_ctx *env, t_line *l);
void			clear_screen_(t_ctx *env, t_line *l);

int				move_cursor_forward(t_ctx *ctx, t_line *l);
int				move_cursor_backward(t_ctx *ctx, t_line *l);

void			go_upper_line(t_ctx *env, t_line *l);
void			go_lower_line(t_ctx *env, t_line *l);
void			go_beginning(t_ctx *env, t_line *l);
void			go_end(t_ctx *env, t_line *l);
void			go_prev_word(t_ctx *env, t_line *l);
void			go_next_word(t_ctx *env, t_line *l);

void			print_line_attributes(t_ctx *ctx, t_line *l, t_dlist *list);
void			print_line(t_dlist *list);

void			up_key(t_ctx *env, t_line *l);
void			down_key(t_ctx *env, t_line *l);
void			lkey(t_ctx *env, t_line *l);
void			rkey(t_ctx *env, t_line *l);

void			insert_char(char *buf, t_ctx *env, t_line *l);
void			insert_char_slow(char *buf, t_ctx *ctx, t_line *l);
void			del_prev_char(t_ctx *env, t_line *l);
void			del_curr_char(t_ctx *env, t_line *l);

void			kill_end(t_ctx *env, t_line *l);
void			kill_beginning(t_ctx *env, t_line *l);
void			kill_prev_word(t_ctx *env, t_line *l);
void			kill_next_word(t_ctx *env, t_line *l);
void			yank(t_ctx *env, t_line *l);

bool			test_kill_beginning(t_ctx *env, t_line *l, t_key *key);
bool			test_kill_end(t_ctx *env, t_line *l, t_key *key);
bool			test_kill_prev_word(t_ctx *env, t_line *l, t_key *key);
bool			test_kill_next_word(t_ctx *env, t_line *l, t_key *key);
bool			test_clear_screen(t_ctx *env, t_line *l, t_key *key);
bool			test_yank(t_ctx *env, t_line *l, t_key *key);
bool			test_next_word(t_ctx *env, t_line *l, t_key *key);
bool			test_prev_word(t_ctx *env, t_line *l, t_key *key);
bool			test_upper_line(t_ctx *env, t_line *l, t_key *key);
bool			test_lower_line(t_ctx *env, t_line *l, t_key *key);
bool			test_end(t_ctx *env, t_line *l, t_key *key);
bool			test_beginning(t_ctx *env, t_line *l, t_key *key);
bool			test_upkey(t_ctx *env, t_line *l, t_key *key);
bool			test_downkey(t_ctx *env, t_line *l, t_key *key);
bool			test_rkey(t_ctx *env, t_line *l, t_key *key);
bool			test_lkey(t_ctx *env, t_line *l, t_key *key);
bool			test_del_curr_char(t_ctx *env, t_line *l, t_key *key);
bool			test_del_prev_char(t_ctx *env, t_line *l, t_key *key);
bool			test_emacs_mode(t_ctx *env, t_line *l, t_key *key);

void			update_line(t_ctx *env, t_line *l);
void			update_linestate(t_stack **state, char c);
void			get_state(t_line *l);
void			query_linestate(t_dlist *dlst, t_stack **linestate);
void			query_hdocstate(t_dlist *dlst, t_stack **linestate, char *eof);

void			toggle_emacs_mode(t_ctx *env, t_line *l);
void			join_split_lines(t_line *l);
void			err_line(t_line *l, int errno);
void			add_newline(t_line *l);

void			reset_attributes(t_line *l);
void			reset_line(t_ctx *ctx, t_line *l);
void			init_line(t_line *l);

void			handle_paren(t_stack **line, char c);
void			handle_brace(t_stack **line, char c);
void			handle_hash(t_stack **line);

#endif

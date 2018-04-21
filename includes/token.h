/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:30:05 by lportay           #+#    #+#             */
/*   Updated: 2018/04/21 14:16:00 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define R_LESS (LESS | DLESS | TLESS | LESSAND)
# define R_GREAT (GREAT | DGREAT | GREATAND)
# define R_AND (ANDGREAT | ANDDGREAT)
# define RDIR (R_LESS | R_GREAT | R_AND)
# define QUOT (BSLASH | SQUOTE | DQUOTE | BQUOTE)

# define FMT_SYN ("42sh: syntax error near unexpected token %s\n")

/*
**	NEWLINE 				\n
**	SEMICOL					;
**	IO_NUMBER				*[0-9]>|*[0-9]<
**	WORD					Everything else...
**	ASSIGNMENT_WORD			NAME=
**
**	OR						 |
**	AND,					 &
**	LESS 					 <
**	GREAT 					 >
**	OR_IF 					 ||
**	AND_IF  				 &&
**	DLESS					 << (HEREDOC)
**	DGREAT					 >>
**	LESSAND 				 <&
**	GREATAND 				 >&
**	TLESS					 <<<
**	ANDGREAT 				 &>
**	ANDDGREAT				 &>>
**
**	COMMENT 				 # *ANY_TOKEN NEWLINE
**
** Maybe add NAME class in a future version
*/

enum	e_toktype
{
	HEAD,
	NEWLINE = 1 << 0,
	SEMICOL = 1 << 1,
	IO_NUMBER = 1 << 2,
	WORD = 1 << 3,
	ASSIGNMENT_WORD = 1 << 4,
	OR = 1 << 5,
	AND = 1 << 6,
	LESS = 1 << 7,
	GREAT = 1 << 8,
	OR_IF = 1 << 9,
	AND_IF = 1 << 10,
	DLESS = 1 << 11,
	DGREAT = 1 << 12,
	LESSAND = 1 << 13,
	GREATAND = 1 << 14,
	TLESS = 1 << 15,
	ANDGREAT = 1 << 16,
	ANDDGREAT = 1 << 17,
	COMMENT = 1 << 20,
	TOKERR = 1 << 21
};

/*
** Quotes and Heredoc injects '\n'
*/

enum	e_linestate
{
	UNQUOTED = 1 << 0,
	BSLASH = 1 << 1,
	SQUOTE = 1 << 2,
	DQUOTE = 1 << 3,
	BQUOTE = 1 << 4,
	PAREN = 1 << 5,
	BRACE = 1 << 6,
	HEREDOC = 1 << 7,
	ERROR = 1 << 8,
	DOLLAR = 1 << 9,
	HASH = 1 << 10,
	DOLLBRACE = DOLLAR | BRACE,
	DOLLPAREN = DOLLAR | PAREN,
};

typedef struct		s_token
{
	t_dlist			*first_letter;
	t_dlist			*last_letter;
	struct s_token	*next;
	enum e_toktype	type;
}					t_token;

typedef struct		s_redir
{
	t_dlist			*first_letter;
	t_dlist			*last_letter;
	struct s_token	*next;
	enum e_toktype	type;
	int				lhs;
	char			*s_rhs;
	int				fd_rhs;
	bool			dash;
}					t_redir;

typedef struct		s_heredoc
{
	t_dlist			*first_letter;
	t_dlist			*last_letter;
	struct s_token	*next;
	enum e_toktype	type;
	int				lhs;
	char			*s_rhs;
	int				glob;
	t_line			hdoc;
}					t_heredoc;

char				*str_from_token(t_token *tok, int toktype);

void				init_token_table(t_kvp *tok);
void				dump_token(t_token *tok);
void				print_toklist(t_token *toklist);
t_token				*new_token(t_dlist *line);

void				clear_following_redirs(t_token *toklist);
void				delete_toklist(t_token **toklist);

void				tokrules(t_token *last_tok, t_dlist *line, t_stack **quote);

t_token				*tokenizer(t_dlist *line);

t_token				*filter_token_loop(t_token **toklist, t_token **prev);

int					is_metachar(char c);
int					is_quoting(char c);
int					is_max_operator(int n);
int					is_extendable_operator(int n);

int					extend_word(t_token *token, char c, int quote_state);
int					extend_operator(t_token *token, char c, int quote_state);
int					token_type(char c, int quote_state);

#endif

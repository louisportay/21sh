/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:30:05 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 10:53:45 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H


# define R_LESS (LESS | DLESS | TLESS | LESSAND)
# define R_GREAT (GREAT | DGREAT | GREATAND)
# define R_AND (ANDGREAT | ANDDGREAT)

# define REDIR (R_LESS | R_GREAT | R_AND)

# define IS_LESS_REDIR(n) (n & (LESS | DLESS | TLESS | LESSAND))
# define IS_GREAT_REDIR(n) (n & (GREAT | DGREAT | GREATAND))
# define IS_AND_REDIR(n) (n & (ANDGREAT | ANDDGREAT))
# define ISREDIR(n) (IS_LESS_REDIR(n) | IS_GREAT_REDIR(n) | IS_AND_REDIR(n))

//c'est pas trop a la norme cette macro, a changer apres
# define IS_MAX_OPE(n) (n & (OR_IF | AND_IF | DGREAT | LESSAND | GREATAND | ANDDGREAT | TLESS | DOLLAR | BANG | NEWLINE | SEMICOL))

# define IS_NOT_MAX_OPE(n) (n & (OR | AND | LESS | GREAT | DLESS | ANDGREAT))
# define IS_WORD_IO_NUMBER(n) (n & (WORD | ASSIGNMENT_WORD | IO_NUMBER))

enum	e_toktype
{
		HEAD,

		NEWLINE = 1 << 0, 				// \n
		SEMICOL = 1 << 1,				// ;
		IO_NUMBER = 1 << 2,				// *[0-9]>|*[0-9]<
		WORD = 1 << 3,       			// Everything else...
		ASSIGNMENT_WORD = 1 << 4, 		// WORD=

		OR = 1 << 5,					// |
		AND = 1 << 6,					// &
		LESS = 1 << 7,					// <
		GREAT = 1 << 8,					// >
		OR_IF = 1 << 9,					// ||
		AND_IF = 1 << 10, 				// &&
		DLESS = 1 << 11,				// << (HEREDOC)
		DGREAT = 1 << 12,				// >>
		LESSAND = 1 << 13,				// <&
		GREATAND = 1 << 14,				// >&
		TLESS = 1 << 15,				// <<<
		ANDGREAT = 1 << 16,				// &>
		ANDDGREAT = 1 << 17,			// &>>

		DOLLAR = 1 << 18,				// $
		BANG = 1 << 19,					// !

		COMMENT = 1 << 20,				// # *ANY_TOKEN NEWLINE
		PARAM_EXP = DOLLAR | WORD,		// ${} | $VAR
//		PARAM_EXP = DOLLAR | 1 << 0,	// ${} | $VAR
		CMD_SUB = DOLLAR | WORD,		// $() |	bquotes+grouping --> 42SH
//		CMD_SUB = DOLLAR | 1 << 2,		// $() |	bquotes+grouping --> 42SH
		ARI_EXP = DOLLAR | WORD,		// $[] | $((MATHS))
//		ARI_EXP = DOLLAR | 1 << 3,		// $[] | $((MATHS))
};

typedef struct		s_token
{
	t_dlist 		*first_letter;
	t_dlist 		*last_letter;
	struct s_token	*next;
	enum e_toktype	type;
}					t_token;

typedef struct		s_redir
{
	t_dlist 		*first_letter;
	t_dlist 		*last_letter;
	struct s_token	*next;
	enum e_toktype	type;

	int				lhs;
	char			*s_rhs;
	int				fd_rhs;
	bool			dash;
}					t_redir;

typedef struct		s_heredoc
{
	t_dlist 		*first_letter;
	t_dlist 		*last_letter;
	struct s_token	*next;
	enum e_toktype	type;

	int				lhs;
	char			*s_rhs;
	t_line			hdoc;
}					t_heredoc;

char				*token_str(t_token *tok);
void				delete_toklist(t_token **toklist);
void				dump_token(t_token *tok);
t_token				*tokenizer(t_dlist *line);

t_token				*filter_tokens(t_token *toklist);// static ?

void    			print_toklist(t_token *toklist);

#endif

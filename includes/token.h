/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:30:05 by lportay           #+#    #+#             */
/*   Updated: 2018/01/29 18:24:31 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

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

		DOLLAR = 1 << 17,				// $
		BANG = 1 << 18,					// !

		COMMENT = 1 << 19,				// # *ANY_TOKEN NEWLINE
		PARAM_EXP = DOLLAR | 1 << 0,	// ${} | $VAR
		CMD_SUB = DOLLAR | 1 << 2,		// $() |	bquotes+grouping --> 42SH
		ARI_EXP = DOLLAR | 1 << 3,		// $[] | $((MATHS))
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

	int				left_op;
	int				fd_right_op;
	char			*s_right_op;
	bool			dash;
}					t_redir;

char	*token_str(t_token *tok);
void	delete_toklist(t_token **toklist);
void	dump_token(t_token *tok);
t_token	*tokenizer(t_dlist *line);

t_token	*filter_tokens(t_token *toklist);// static ?


#endif

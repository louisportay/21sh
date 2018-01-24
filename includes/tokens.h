/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:25:40 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/24 16:50:11 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "ft_dlist.h"
enum    e_toktype
{
        HEAD,

        NEWLINE = 1 << 0,                 // \n
        SEMICOL = 1 << 1,                // ;
        IO_NUMBER = 1 << 2,                // *[0-9]>|*[0-9]<
        WORD = 1 << 3,                   // Everything else...
        ASSIGNMENT_WORD = 1 << 4,         // WORD=

        OR = 1 << 5,                    // |
        AND = 1 << 6,                    // &
        LESS = 1 << 7,                    // <
        GREAT = 1 << 8,                    // >
        OR_IF = 1 << 9,                    // ||
        AND_IF = 1 << 10,                 // &&
        DLESS = 1 << 11,                // << (HEREDOC)
        DGREAT = 1 << 12,                // >>
        LESSAND = 1 << 13,                // <&
        GREATAND = 1 << 14,                // >&
        TLESS = 1 << 15,                // <<<
        ANDGREAT = 1 << 16,                // &>

        DOLLAR = 1 << 17,                // $
        LPAREN = 1 << 18,                // (
        RPAREN = 1 << 19,                // )
        LBRACE = 1 << 20,                // {
        RBRACE = 1 << 21,                // }
        LBRACK = 1 << 22,                // [
        RBRACK = 1 << 23,                // ]

        BANG = 1 << 24,                    // !
        COMMENT = 1 << 25,                // # *ANY_TOKEN NEWLINE

        BANG_EXP = BANG | WORD,
        PARAM_EXP = DOLLAR | LBRACE,    // ${} | $VAR
        CMD_SUB = DOLLAR | LPAREN,        // $() |    Backquotes+grouping --> 42SH 
        ARI_EXP = DOLLAR | LBRACK,        // $[] | $((MATHS))    
};

typedef struct        s_token
{
    t_dlist         *first_letter;
    t_dlist         *last_letter;
    struct s_token    *next;
    enum e_toktype    type;
}                    t_token;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:42:03 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/10 18:37:06 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_21sh.h"

typedef struct s_ptok	t_ptok;
typedef struct s_asmt	t_asmt;

struct					s_asmt
{
	char				*key;
	char				*value;
	struct s_asmt		*next;
};

struct					s_ptok
{
	struct s_job		*job;
	struct s_ptok		*ok;
	struct s_ptok		*err;
	struct s_ptok		*next;
};

void					ptok_free(struct s_ptok **tok);
void					ptok_clear(struct s_ptok **tokens);

void					ptok_print(struct s_ptok *tokens);

struct s_ptok			*parser(struct s_token *tokens);

t_asmt					*asmt_fromtoken(t_token *asmt);
void					asmt_update(t_asmt *asmt, t_asmt **new);
void					asmt_insert(t_asmt **head, t_asmt **curr, t_asmt *e);
t_asmt					*asmt_find(t_asmt *asmt, char *key);
void					asmt_print(t_asmt *asmt);

/*
**	BRIDGES
*/

char					*dlst_pstr(t_dlist *beg, t_dlist *end);
size_t					dlst_pcount(t_dlist *beg, t_dlist *end);
t_dlist					*dlst_findc(t_dlist *elem, char c);

void					token_insert(t_token **head, t_token **curr,
										t_token *e);
size_t					token_count(t_token *tok);

#endif

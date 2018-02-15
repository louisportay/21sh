/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:42:03 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/14 17:08:53 by vbastion         ###   ########.fr       */
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
	int					fg;
	struct s_job		*job;
	struct s_ptok		*ok;
	struct s_ptok		*err;
	struct s_ptok		*next;
};

void					ptok_free(struct s_ptok **tok);
void					*ptok_clear(struct s_ptok **tokens);
void					ptok_insert(struct s_ptok **head, struct s_ptok **curr,
									struct s_ptok *e);

void					ptok_print(struct s_ptok *tokens);

struct s_ptok			*parser(struct s_token *tokens);

struct s_proc			*proc_next(struct s_token **tokens);

struct s_asmt			*asmt_fromtoken(struct s_token *asmt);
void					asmt_update(struct s_asmt *asmt, struct s_asmt **new);
void					asmt_insert(struct s_asmt **head, struct s_asmt **curr,
									struct s_asmt *e);
struct s_asmt			*asmt_find(struct s_asmt *asmt, char *key);
void					asmt_free(struct s_asmt **asmt);
void					asmt_clear(struct s_asmt **asmt);

/*
**	BRIDGES
*/

char					*dlst_pstr(struct s_dlist *beg, struct s_dlist *end);
size_t					dlst_pcount(struct s_dlist *beg, struct s_dlist *end);
struct s_dlist			*dlst_findc(struct s_dlist *elem, char c);

void					token_insert(struct s_token **head,
										struct s_token **curr,
										struct s_token *e);
size_t					token_count(struct s_token *tok);
int						token_issep(struct s_token *tok);
void					*token_dumperror(struct s_token *tok);
struct s_redir			*redir_dup(struct s_redir *redir);

char					**astr_fromlist(struct s_list *list);

/*
 *						DEBUG ONLY | COMMENT SYNTAX ON PURPOSE
 */

void					asmt_print(struct s_asmt *asmt);
void					astr_print(char **astr);
void					job_print(struct s_job *job);
void					redir_print(struct s_redir *redir);

#endif

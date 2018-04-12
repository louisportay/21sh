/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:48:28 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/12 12:54:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_PARAM_H
# define EXPAND_PARAM_H

# include "ft_21sh.h"

# include "expand.h"

# define VACHR ("${} \"_?")
# define VAR_OK 1
# define VAR_ERR -1
# define VAR_KO 0

# define VAR_NOSTATE ("Missing a state\n")

# define PARAM_DEPTH 8

typedef struct s_vtok	t_vtok;
typedef struct s_lvar	t_lvar;

enum					e_vtype
{
	VADOLL = 0,
	VAOBRA,
	VACBRA,
	VSPACE,
	VDQUOT,
	VUNDER,
	VQUEST,
	VAWORD,
	VOTHER
};

union					u_vdat
{
	char				*str;
	char				c;
};

struct					s_vtok
{
	enum e_vtype		type;
	union u_vdat		data;
	t_vtok				*next;
};

struct					s_lvar
{
	t_ctx				*ctx;
	t_qbuf				*buf;
	t_vtok				*tokens;
	t_vtok				*curr_tok;
	int					exit_code;
	char				*exit_message;
	void				(*next)(t_lvar *lvar);
};

int						expand_param(char *str, char **ret, t_ctx *ctx);

int						scan_dollar(char *str);

int						vtok_sanitize(t_vtok *tokens, int depth, int *err);
int						vtok_matching(t_vtok *curr, t_vtok **matched);
t_vtok					*vtok_san_getnext(t_vtok *tok);

int						vtok_isopen(t_vtok *curr);
void					vtok_conv(t_vtok *curr);
void					vtok_split(t_vtok *tok, enum e_vtype type,
									t_vtok **next);

void					vtok_insert(t_vtok **head, t_vtok **curr,
									t_vtok *tmp);
t_vtok					*vtok_new(enum e_vtype type, char c);
t_vtok					*vtok_newstr(enum e_vtype type, char *str);
void					vtok_del(t_vtok **tok);

int						vtok_assert(t_vtok *tok, int n, enum e_vtype type);
int						vtok_move(t_vtok **tok, int n);
t_vtok					*vtok_peek(t_vtok *tok, int n);
t_vtok					*vtok_peek_if(t_vtok *tok, int n, enum e_vtype type);

t_vtok					*vtok_get(char *str, int *err);

void					vtok_tobuf(t_vtok *tok, t_qbuf *buf);
void					vtok_print(t_vtok *tok);
void					vtok_printone(t_vtok *tok);

int						vtok_handletokens(t_vtok *tokens, char **ret,
											t_ctx *ctx);

void					vtok_start(t_lvar *lvar);
t_vtok					*vtok_last(t_vtok *last);

void					vtok_addvar(t_qbuf *buf, t_ctx *ctx, char *key);
void					vtok_vadoll(t_lvar *lvar);
void					vtok_dollvaobra(t_lvar *lvar);
void					vtok_dolldoll(t_lvar *lvar);
void					vtok_dollword(t_lvar *lvar);
void					vtok_dollunder(t_lvar *lvar);
void					vtok_dollquest(t_lvar *lvar);
void					vtok_addpid(t_qbuf *buf, int clear);
void					vtok_dollexec(t_lvar *lvar, char *str[2], char c);

int						vtok_counttil(t_vtok *head, enum e_vtype type);
t_vtok					*vtok_getclose(t_vtok *tok);
void					vtok_splittilclose(t_vtok *tok, t_vtok **next);

int						vtok_isword(char *str);

void					vtok_clear(t_vtok **tok);

t_vtok					*vtok_get_next(t_vtok *tok, int depth, int *err);

#endif

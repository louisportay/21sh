/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:48:28 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/14 17:59:00 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_PARAM_H
# define EXPAND_PARAM_H

# include "ft_membuf.h"
# include "ft_environ.h"

# include "expand.h"
# include "ft_delegates.h"

# define VACHR ("${} \"")
# define VAR_OK 1
# define VAR_ERR -1
# define VAR_KO 0

# define VAR_NOSTATE ("Missing a state\n")

typedef struct s_vtok	t_vtok;
typedef struct s_lvar	t_lvar;

enum					e_vtype
{
	VADOLL = 0,
	VAOBRA,
	VACBRA,
	VSPACE,
	VDQUOT,
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
	t_environ			*env;
	t_membuf			buf;
	t_vtok				*tokens;
	t_vtok				*curr_tok;
	int					exit_code;
	char				*exit_message;
	void				(*next)(t_lvar *lvar);
};

int						expand_param(char **str, t_environ *env);

int						scan_dollar(char *str);

void					vtok_sanitize(t_vtok *tokens);
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

t_vtok					*vtok_get(char *str);

void					vtok_tobuf(t_vtok *tok, t_membuf *buf);
void					vtok_print(t_vtok *tok);
void					vtok_printone(t_vtok *tok);

int						vtok_handletokens(t_vtok *tokens, char **ret,
											t_environ *env);

void					vtok_start(t_lvar *lvar);
t_vtok					*vtok_last(t_vtok *last);

void					vtok_addvar(t_membuf *buf, t_environ *env, char *key);
void					vtok_vadoll(t_lvar *lvar);
void					vtok_dollvaobra(t_lvar *lvar);
void					vtok_dolldoll(t_lvar *lvar);
void					vtok_addpid(t_membuf *buf, int clear);
void					vtok_dollexec(t_lvar *lvar, char *str[2], char c);

int						vtok_counttil(t_vtok *head, enum e_vtype type);
t_vtok					*vtok_getclose(t_vtok *tok);
void					vtok_splittilclose(t_vtok *tok, t_vtok **next);

int						vtok_isword(char *str);

void					vtok_clear(t_vtok **tok);

#endif

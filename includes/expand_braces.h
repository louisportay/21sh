/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_braces.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:48:01 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/11 19:07:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_BRACES_H
# define EXPAND_BRACES_H

# include <stdlib.h>

# include "ft_21sh.h"

typedef struct s_btok	t_btok;
typedef struct s_ttok	t_ttok;

enum					e_btoktype
{
	BROBRA,
	BRCBRA,
	BCOMMA,
	BPOINT,
	BRDOLL,
	BOTHER
};

enum					e_ttoktype
{
	TNUMRNG,
	TALPRNG,
	TMIXRNG,
	TSTRING
};

union					u_tdata
{
	int					rng[3];
	char				*str;
	t_list				*elem[2];
};

struct					s_btok
{
	enum e_btoktype		type;
	char				*val;
	t_btok				*next;
};

struct					s_ttok
{
	enum e_ttoktype		type;
	union u_tdata		data;
	t_ttok				*next;
};

int						expand_braces(char *str, char **ret);

int						braces_scan(char *str);

t_btok					*btok_get(char *str, int *err);

int						btok_sanitize(t_btok *toks);
t_btok					*btok_san_getnext(t_btok *tok);

t_btok					*btok_new(enum e_btoktype type, char *str);
void					btok_free(t_btok **tok);
void					btok_clear(t_btok **tok);
void					btok_insert(t_btok **head, t_btok **curr, t_btok *tmp);

t_btok					*btok_from_squote(char **str, int *err);
t_btok					*btok_from_dquote(char **str, int *err);
t_btok					*btok_from_other(char **str);

void					btok_print(t_btok *tok);
void					btok_printone(t_btok *tok);

t_btok					*btok_peek(t_btok *tok, int n);
int						btok_assert(t_btok *tok, int n, enum e_btoktype type);

t_ttok					*ttok_get(t_btok *tok);

char					*ttok_combine(t_ttok *tok);

void					ttok_clear(t_ttok **tok);

int						btok_match(t_btok *head, int *es);
t_ttok					*ttok_flatten(t_btok **head);

t_ttok					*ttok_newrng(enum e_ttoktype type, int l, int r);
t_ttok					*ttok_newmix(t_list *lst);
t_ttok					*ttok_newstr(char *str);
t_ttok					*ttok_compose(t_btok **btok);
void					ttok_insert(t_ttok **head, t_ttok **curr, t_ttok *tmp);
void					ttok_clear(t_ttok **tok);

void					ttok_printone(t_ttok *tok);
void					ttok_print(t_ttok *toks);

char					*ttok_combine(t_ttok *toks);
t_ttok					*ttok_comb(t_ttok *tok);
char					*ttok_tostr(t_ttok *tok);

t_btok					*ttok_before(t_btok *next, t_btok *from);

t_ttok					*ttok_do_mix(t_btok **head);

int						ft_islet(char *str);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:28:23 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/11 19:54:10 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define TK_ASN (REDIR | ASSIGNMENT_WORD)
#define TK_WORD (REDIR | WORD)

static char				**get_args(t_token **toks, t_redir **rdr)
{
	t_list				*lsts[3];
	t_token				*t;
	t_token				*tmp;
	char				*word;
	char				**av;

	lsts[0] = NULL;
	t = *toks;
	while (t != NULL && (t->type & TK_WORD) != 0)
	{
		tmp = t;
		t = t->next;
		if (tmp->type & WORD)
		{
			word = dlst_pstr(tmp->first_letter, tmp->last_letter->next);
			lsts[2] = list_create(word);
			ft_list_insert(lsts, lsts + 1, lsts[2]);
		}
		else
		{
			token_insert((t_token **)rdr, (t_token **)rdr + 1,
							(t_token *)redir_dup((t_redir *)tmp));
		}
	}
	av = astr_fromlist(lsts[0]);
	ft_memdel((void **)lsts);
	*toks = t;
	return (av);
}

static t_asmt			*get_asmt(t_token **toks, t_redir **rdr)
{
	t_token				*t;
	t_token				*tmp;
	t_asmt				*asmt[3];
	t_asmt				*exist;

	t = *toks;
	asmt[0] = NULL;
	while (t != NULL && (t->type & TK_ASN) != 0)
	{
		tmp = t;
		t = t->next;
		if (tmp->type == ASSIGNMENT_WORD)
		{
			asmt[2] = asmt_fromtoken(tmp);
			if ((exist = asmt_find(asmt[0], asmt[2]->key)) != NULL)
				asmt_update(exist, asmt + 2);
			else
				asmt_insert(asmt + 0, asmt + 1, asmt[2]);
		}
		else
		{
			token_insert((t_token **)rdr, (t_token **)rdr + 1,
							(t_token *)redir_dup((t_redir *)tmp));
		}
	}
	*toks = t;
	return (asmt[0]);
}

t_proc					*proc_next(t_token **tokz)
{
	t_redir				*rdr[2];
	t_proc				*p;

	rdr[0] = NULL;
	if (token_issep(*tokz))
	{
		token_dumperror(*tokz);
		return (NULL);
	}
	p = (t_proc *)ft_pmemalloc(sizeof(t_proc), &on_emem, NOMEM);
	p->asmts = get_asmt(tokz, rdr);
	p->argv = get_args(tokz, rdr);
	p->redirs = rdr[0];
	return (p);
}

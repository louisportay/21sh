/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:28:23 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 18:29:46 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

#define TK_ASN (RDIR | ASSIGNMENT_WORD)
#define TK_WORD (RDIR | WORD)

static int				get_args_loop(t_token *tok[3], t_list *lsts[3],
										t_redir **rdr)
{
	char				*word;

	tok[1] = tok[0];
	tok[0] = tok[0]->next;
	if (tok[1]->type & (WORD | ASSIGNMENT_WORD))
	{
		word = dlst_pstr(tok[1]->first_letter, tok[1]->last_letter->next);
		lsts[2] = list_create(word);
		ft_list_insert(lsts, lsts + 1, lsts[2]);
	}
	else
	{
		if ((tok[2] = (t_token *)redir_dup((t_redir *)tok[1])) == NULL)
		{
			ft_list_clear(lsts, &ft_memdel);
			return (1);
		}
		else
			token_insert((t_token **)rdr, (t_token **)rdr + 1, tok[2]);
	}
	return (0);
}

static char				**get_args(t_token **toks, t_redir **rdr)
{
	t_list				*lsts[3];
	t_token				*tok[3];
	char				**av;

	lsts[0] = NULL;
	tok[0] = *toks;
	while (tok[0] != NULL && (tok[0]->type & (TK_WORD | TK_ASN)) != 0)
	{
		if (get_args_loop(tok, lsts, rdr) != 0)
			return ((void *)-1);
	}
	av = astr_fromlist(lsts);
	*toks = tok[0];
	return (av);
}

static int				get_asmt_loop(t_token *tok[3], t_asmt *asmt[3],
										t_redir **rdr)
{
	t_asmt				*exist;

	tok[1] = tok[0];
	tok[0] = tok[0]->next;
	if (tok[1]->type == ASSIGNMENT_WORD)
	{
		asmt[2] = asmt_fromtoken(tok[1]);
		if ((exist = asmt_find(asmt[0], asmt[2]->key)) != NULL)
			asmt_update(exist, asmt + 2);
		else
			asmt_insert(asmt + 0, asmt + 1, asmt[2]);
	}
	else
	{
		if ((tok[2] = (t_token *)redir_dup((t_redir *)tok[1])) == NULL)
		{
			asmt_clear(asmt);
			return (1);
		}
		else
			token_insert((t_token **)rdr, (t_token **)rdr + 1, tok[2]);
	}
	return (0);
}

static t_asmt			*get_asmt(t_token **toks, t_redir **rdr)
{
	t_token				*tok[3];
	t_asmt				*asmt[3];

	tok[0] = *toks;
	asmt[0] = NULL;
	while (tok[0] != NULL && (tok[0]->type & TK_ASN) != 0)
	{
		if (get_asmt_loop(tok, asmt, rdr) != 0)
			return ((void *)-1);
	}
	*toks = tok[0];
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
	if (p->asmts == (void *)-1 || p->argv == (void *)-1)
	{
		if (p->asmts != (void *)-1)
			asmt_clear(&p->asmts);
		if (p->argv != (void *)-1)
			ft_astr_clear(&p->argv);
		rdir_clear(&p->redirs);
		ft_memdel((void **)&p);
		return (NULL);
	}
	p->pipe_in = -1;
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:32 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/10 19:05:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define TK_ASN (REDIR | ASSIGNMENT_WORD)
#define TK_WORD (REDIR | WORD)

//	void					get(t_proc *p, t_token *tokens,  t_token *ts,
//								enum e_toktype enums[2])
//	{
//		while (t != NULL && (t->type & TK_ASN) != 0)
//		{
//			if (t->type == ASSIGNMENT_WORD)
//				token_insert(asmt, asmt + 1, t);
//			else
//				token_insert((t_token **)&p->redir, (t_token **)&rdr, t);
//			t = t->next;
//		}
//	}

void					asmt_print(t_asmt *asmt)
{
	while (asmt != NULL)
	{
		printf("%s=%s\n", asmt->key, asmt->value);
		asmt = asmt->next;
	}
}

void					astr_print(char **astr)
{
	int					i;

	i = 0;
	while (astr[i] != NULL)
	{
		printf("argv[%d]: %s\n", i, astr[i]);
		i++;
	}
}

void					arguments(t_proc *proc, t_token *args)
{
	size_t				cnt;
	size_t				i;

	cnt = token_count(args);
	proc->argv = (char **)ft_pmemalloc(sizeof(char *) * (cnt + 1),
										&on_emem, NOMEM);
	i = 0;
	while (args != NULL)
	{
		proc->argv[i] = dlst_pstr(args->first_letter, args->last_letter->next);
		args = args->next;
		i++;
	}
	astr_print(proc->argv);
}

void					assign(t_proc *proc, t_token *asmt)
{
	t_asmt				*curr;
	t_asmt				*kv;
	t_asmt				*tmp;

	while (asmt != NULL)
	{
		kv = asmt_fromtoken(asmt);
		if ((tmp = asmt_find(proc->asmts, kv->key)) != NULL)
			asmt_update(tmp, &kv);
		else
			asmt_insert(&proc->asmts, &curr, kv);
		asmt = asmt->next;
	}
	asmt_print(proc->asmts);
}

void					 get(t_proc *p, t_token **toklist, enum e_toktype tar,
								t_token **tar_toklist, t_token **curr_rdr)
{
	t_token				*t;
	t_token				*tmp;
	enum e_toktype		mask;

	mask = tar | REDIR;
	t = *toklist;
	while (t != NULL && (t->type & mask) != 0)
	{
		tmp = t;
		t = t->next;
		if (tmp->type == tar)
			token_insert(tar_toklist, tar_toklist + 1, tmp);
		else
			token_insert((t_token **)&p->redirs, curr_rdr, tmp);
	}
	*toklist = t;
}

t_proc					*proc_next(t_token **tokz)
{
	t_token				*asmt[2];
	t_token				*word[2];
	t_redir				*rdr;
	t_proc				*p;

	p = (t_proc *)ft_pmemalloc(sizeof(t_proc), &on_emem, NOMEM);
	asmt[0] = NULL;
	word[0] = NULL;
	get(p, tokz, ASSIGNMENT_WORD, asmt, (t_token **)&rdr);
	get(p, tokz, WORD, word, (t_token **)&rdr);
	assign(p, asmt[0]);
	arguments(p, word[0]);
	return (p);
}

t_ptok					*parse(struct s_token *tokens)
{
	t_proc				*proc;
	t_token				*tokz;

	tokz = tokens->next;
	proc = proc_next(&tokz);
	return (NULL);		// Later when working I will return sth else
}

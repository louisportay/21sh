/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_match.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:04:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/21 12:16:17 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static char		*get_dirs(t_entry *e, t_entry *entries[2])
{
	struct stat	stats;
	t_entry		*tmp;
	char		*ret;

	while (e != NULL)
	{
		tmp = e;
		e = e->next;
		tmp->next = NULL;
		if (stat(tmp->path, &stats) == -1)
			ent_free(&tmp);
		else if (S_ISDIR(stats.st_mode) == 0)
			ent_free(&tmp);
		else
			ent_insert_one(entries, tmp);
	}
	ret = ent_cat(entries[0], 1);
	ent_clear(entries);
	return (ret);
}

static char		*get_deeper(t_entry *e, t_mtok *tok)
{
	t_entry		*t;
	struct stat	stats;
	t_entry		*entries[2];
	t_entry		*result;

	entries[0] = NULL;
	entries[1] = NULL;
	if (tok == NULL)
		return (get_dirs(e, entries));
	while (e != NULL)
	{
		t = e;
		e = e->next;
		if (stat(t->path, &stats) != -1
			&& (S_ISDIR(stats.st_mode) && (stats.st_mode & S_IRUSR)))
		{
			if (dir_explore(t->path, &result, get_ctxaddr()->set & DOTGLOB
							|| (tok->type == STRIN
								&& tok->data.str[0] == '.')) == -1)
				fatal_err(NOMEM, get_ctxaddr());
			ent_insert(entries, entries + 1, result);
		}
		ent_free(&t);
	}
	return (glob_get_match(entries[0], tok));
}

static void		mtok_assert(t_entry **entries, t_mtok *toks)
{
	t_entry		*e;
	t_entry		*tmp;
	t_entry		*ok[2];

	e = *entries;
	ok[0] = NULL;
	while (e != NULL)
	{
		tmp = e;
		e = e->next;
		if (mtok_match(tmp->name, toks) == 0)
			ent_free(&tmp);
		else
		{
			tmp->next = NULL;
			ent_insert(ok, ok + 1, tmp);
		}
	}
	*entries = ok[0];
}

char			*glob_get_match(t_entry *ents, t_mtok *tok)
{
	t_mtok		*next;
	t_mtok		*last;
	char		*ret;

	last = NULL;
	next = NULL;
	mtok_until_str(tok, "/", &last, &next);
	mtok_assert(&ents, tok);
	if (ents == NULL)
	{
		if (last != NULL)
			last->next = next;
		return (NULL);
	}
	if (last != NULL)
		last->next = next;
	if (next == NULL)
	{
		if ((ret = ent_cat(ents, 0)) == NULL)
			fatal_err(NOMEM, get_ctxaddr());
		ent_clear(&ents);
		return (ret);
	}
	tok = next->next;
	return (get_deeper(ents, tok));
}

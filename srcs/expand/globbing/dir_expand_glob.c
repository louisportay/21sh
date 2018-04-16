/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_expand_glob.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 12:51:49 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/16 18:20:01 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int		mtok_match(char *str, t_mtok *tok);

static int		lmatch_rng(char *str, t_mtok *tok)
{
	if (str == '\0')
		return (0);
	if (ft_strindex(tok->data.str, *str) == -1)
		return (0);
	return (mtok_match(str + 1, tok->next));
}

static int		lmatch_str(char *str, t_mtok *tok)
{
	char		*s;
	size_t		len;

	if (str == '\0')
		return (0);
	s = tok->data.str;
	len = ft_strlen(s);
	if (ft_strncmp(str, s, len) == 0)
		return (mtok_match(str + len, tok->next));
	return (0);
}

static int		lmatch_any(char *str, t_mtok *tok)
{
	if (str == '\0')
		return (0);
	return (mtok_match(str + 1, tok->next));
}

static int		lmatch_fil(char *str, t_mtok *tok)
{
	if (tok->next == NULL)
		return (1);
	while (*str != '\0')
	{
		if (mtok_match(str, tok->next) == 1)
			return (1);
		str++;
	}
	return (0);
}

static int		mtok_match(char *str, t_mtok *tok)
{
	if (str == NULL || (*str == '\0' && tok != NULL && tok->type != STRIN))
		return (0);
	if (tok == NULL)
		return (*str == '\0');
	if (tok->type == ANYSI)
		return (lmatch_any(str, tok));
	else if (tok->type == STRIN)
		return (lmatch_str(str, tok));
	else if (tok->type == RANGE)
		return (lmatch_rng(str, tok));
	else if (tok->type == FILEN)
		return (lmatch_fil(str, tok));
	return (0);
}

static int		show_hidden(t_mtok *tok)
{
	return (get_ctxaddr()->set & DOTGLOB
			|| (tok->type == STRIN && tok->data.str[0] == '.'));
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

static char		*get_match(t_entry *ents, t_mtok *tok)
{
	t_mtok		*next;
	t_mtok		*last;
	char		*ret;
	int			deeper;

	deeper = mtok_until_str(tok, "/", &last, &next);
	mtok_assert(&ents, tok);
	if (ents == NULL)
		return (NULL);
	if (next == NULL)
	{
		if ((ret = ent_cat(ents)) == NULL)
			fatal_err(NOMEM, get_ctxaddr());
		ent_clear(&ents);
		return (ret);
	}
/*
**	Deserves to be splitted.
*/
	last->next = next;
	tok = next->next;
	t_entry *e;
	t_entry	*t;
	struct stat	stats;
	t_entry	*entries[2];
	t_entry	*result;


	e = ents;
	entries[0] = NULL;
	while (e != NULL)
	{
		t = e;
		e = e->next;
		if (stat(t->path, &stats) != -1
			&& (S_ISDIR(stats.st_mode) && (stats.st_mode & S_IRUSR)))
		{
			if (dir_explore(t->path, &result, get_ctxaddr()->set & DOTGLOB
						|| (tok->type == STRIN && tok->data.str[0] == '.')) == -1)
				fatal_err(NOMEM, get_ctxaddr());
			ent_insert(entries, entries + 1, result);
		}
		{	/*	Append it's results	*/	}
		ent_free(&t);
	}
	return (get_match(entries[0], tok));
}

char			*glob_match(t_mtok *tok)
{
	char		buf[MAXPATHLEN + 1];
	t_entry		*ents;
	char		*ret;

	ret = NULL;
	if (tok->type == STRIN && tok->data.str[0] == '/')
	{
		dir_explore("/", &ents, get_ctxaddr()->set & DOTGLOB);
		tok = tok->next;
	}
	else
	{
		ft_bzero(buf, MAXPATHLEN + 1);
		dir_explore(NULL, &ents, show_hidden(tok));
	}
	return (get_match(ents, tok));
}

int				do_expand_glob(char **str)
{
	t_mtok		*or;
	t_mtok		*new;
//	t_entry		*matched;
//	int			lret;
	char		*ret;

	or = NULL;
	get_matcher_tokens(*str, &or);
	new = mtok_splitstr(or);
	mtok_clear(&or);
	new = mtok_requal(new);
//	mtok_print(new);
	if ((ret = glob_match(new)) != NULL)
	{
		ft_strdel(str);
		*str = ret;
	}
	mtok_clear(&new);
	return (ret != NULL);
}

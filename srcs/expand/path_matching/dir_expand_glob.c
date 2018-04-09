/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_expand_glob.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 12:51:49 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/09 17:32:29 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_matching.h"
#include "dir_explorer.h"

static int		proceed(t_mtok *tok, t_entry **matched, t_entry *dats)
{
	t_mtok		*next;
	int			ret;

	mtok_until_str(tok, "/", &next);
	dats = ent_matching(tok, dats);
	ret = handle_matched(next, matched, dats);
	mtok_last(tok)->next = next;
	return (ret);
}

static int		is_sep_tok(t_mtok *tok)
{
	return (tok != NULL && tok->type == STRIN
			&& ft_strcmp(tok->data.str, "/") == 0);
}

int				path_match(t_mtok *tok, t_entry **matched)
{
	t_entry		*dats;
	int			ret;

	ret = 0;
	if (tok->type == STRIN)
	{
		if (tok->next == NULL)
			return (0);
		else if (is_sep_tok(tok))
		{
			ret = dir_explore("/", &dats);
			tok = tok->next;
		}
		else if (is_sep_tok(tok->next))
		{
			ret = dir_explore(tok->data.str, &dats);
			tok = tok->next->next;
		}
		else
			ret = dir_explore(tok->data.str, &dats);
	}
	else
		ret = dir_explore(NULL, &dats);
	if (ret < 1)
		return (ret);
	return (tok == NULL ? 0 : proceed(tok, matched, dats));
}

static int		no_exp(t_mtok *new)
{
	while (new != NULL)
	{
		if (new->type != STRIN)
			return (0);
		new = new->next;
	}
	return (1);
}

static void		preclear_mtok(t_mtok *tok)
{
	while (tok)
	{
		ft_strdel(&tok->data.str);
		tok = tok->next;
	}
}

int				do_expand_glob(char **str)
{
	t_mtok		*or;
	t_mtok		*new;
	t_entry		*matched;
	int			lret;

	or = NULL;
	get_matcher_tokens(*str, &or);
	new = mtok_splitstr(or);
	mtok_clear(&or);
	new = mtok_requal(new);
	if (no_exp(new))
	{
		mtok_clear(&new);
		//======= leak here
		return (1);
	}
	if ((lret = path_match(new, &matched)) <= 0)
	{
		preclear_mtok(new);	//	TO BE CHECKED, but seems DUMB AF and duplicate
		mtok_clear(&new);
		return (lret);
	}
	else if (matched == NULL)
	{
		mtok_clear(&new);
		return (0);
	}
	free(*str);
	*str = ent_cat(matched);
	ent_clear(&matched);
	mtok_clear(&new);
	return (*str != NULL ? 1 : -1);
}

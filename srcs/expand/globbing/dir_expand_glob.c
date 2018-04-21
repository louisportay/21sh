/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_expand_glob.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 12:51:49 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 15:15:40 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int		show_hidden(t_mtok *tok)
{
	return (get_ctxaddr()->set & DOTGLOB
			|| (tok->type == STRIN && tok->data.str[0] == '.'));
}

char			*glob_match(t_mtok *tok)
{
	char		buf[MAXPATHLEN + 1];
	t_entry		*ents;

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
	return (glob_get_match(ents, tok));
}

int				do_expand_glob(char **str)
{
	t_mtok		*or;
	t_mtok		*new;
	char		*ret;

	or = NULL;
	get_matcher_tokens(*str, &or);
	new = mtok_splitstr(or);
	mtok_clear(&or);
	new = mtok_requal(new);
	if ((ret = glob_match(new)) != NULL)
	{
		ft_strdel(str);
		*str = ret;
	}
	mtok_clear(&new);
	return (ret != NULL);
}

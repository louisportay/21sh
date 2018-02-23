/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 15:31:48 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/23 15:35:15 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_matching.h"
#include "dir_explorer.h"

// Loads of norm in here to do

#define GLOBSTAR 0x0

t_mtok			*mtok_requal(t_mtok *mtk)
{
	t_mtok		*ok[2];
	t_mtok		*err[2];
	t_mtok		*t;
	int			globstar;

	globstar = get_ctxaddr(NULL)->set & GLOBSTAR;
	ok[0] = NULL;
	ok[1] = NULL;
	err[0] = NULL;
	err[1] = NULL;
	while (mtk != NULL)
	{
		t = mtk;
		mtk = t->next;
		t->next = NULL;
		if (t->type != FILEN && t->type != DIREC)
			mtok_insert(ok, ok + 1, t);
		else if (ok[1] == NULL && (t->type == FILEN
									|| (t->type == DIREC && globstar)))
			mtok_insert(ok, ok + 1, t);
		else if (ok[1] == NULL && t->type == DIREC && globstar == 0)
		{
			t->type = FILEN;
			mtok_insert(ok, ok + 1, t);
			t = mtok_create_str(STRIN, ft_strdup("/"));
			mtok_insert(ok, ok + 1, t);
		}
		else if (t->type == FILEN && ok[1]->type == FILEN)
			mtok_insert(err, err + 1, t);
		else if (t->type == FILEN && ok[1]->type != FILEN)
			mtok_insert(ok, ok + 1, t);
		else if (t->type == DIREC && globstar && ok[1]->type == FILEN)
		{
			ok[1]->type = DIREC;
			ft_memdel((void **)&t);
		}
		else if (t->type == DIREC && globstar && ok[1]->type != FILEN)
			mtok_insert(ok, ok + 1, t);
		else if (t->type == DIREC && globstar == 0 && ok[1]->type == FILEN)
		{
			t->type = STRIN;
			t->data.str = ft_strdup("/");
			mtok_insert(ok, ok + 1, t);
		}
		else if (t->type == DIREC && globstar == 0 && ok[1]->type != FILEN)
		{
			t->type = FILEN;
			mtok_insert(ok, ok + 1, t);
			t = mtok_create_str(STRIN, ft_strdup("/"));
			mtok_insert(ok, ok + 1, t);
		}
	}
	return (ok[0]);
}
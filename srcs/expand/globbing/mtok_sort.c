/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 15:31:48 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/12 18:29:49 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

#define GLOBSTAR 0x0

/*
**	THIS IS PLACEHOLDER
*/

t_mtok			*mtok_requal_glob(t_mtok *mtk)
{
	mtok_clear(&mtk);
	return (NULL);
}

t_mtok			*mtok_requal(t_mtok *mtk)
{
	if (get_ctxaddr()->set & GLOBSTAR)
		return (mtok_requal_glob(mtk));
	t_mtok		**ok;
	t_mtok		*tmp;
	t_mtok		*created;
	int			filen;

	ok = (t_mtok *[]){NULL, NULL};
	filen = 0;
	while (mtk != NULL)
	{
		tmp = mtk;
		mtk = mtk->next;
		tmp->next = NULL;
		if (tmp->type != FILEN && tmp->type != DIREC)
		{
			filen = 0;
			mtok_insert(ok, ok + 1, tmp);
		}
		else if (tmp->type == FILEN)
		{
			if (filen)
				mtok_clear(&tmp);
			else
				mtok_insert(ok, ok + 1, tmp);
			filen = 1;
		}
		else if (tmp->type == DIREC)
		{
			if (filen == 0)
			{
				created = mtok_create(FILEN);
				mtok_insert(ok, ok + 1, created);
			}
			tmp->type = STRIN;
			tmp->data.str = ft_strdup("/");
			mtok_insert(ok, ok + 1, tmp);
			filen = 0;
		}
	}
	return (ok[0]);
}

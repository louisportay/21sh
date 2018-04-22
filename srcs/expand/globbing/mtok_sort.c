/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 15:31:48 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/22 20:25:54 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

#define GLOBSTAR 0x0

static void		mtok_direc(t_mtok *tmp, t_mtok **ok, int *filen)
{
	t_mtok		*created;

	if (*filen == 0)
	{
		created = mtok_create(FILEN);
		mtok_insert(ok, ok + 1, created);
	}
	tmp->type = STRIN;
	tmp->data.str = ft_strdup("/");
	mtok_insert(ok, ok + 1, tmp);
	*filen = 0;
}

static void		mtok_filen(t_mtok *tmp, t_mtok **ok, int *filen)
{
	if (*filen)
		mtok_clear(&tmp);
	else
		mtok_insert(ok, ok + 1, tmp);
	*filen = 1;
}

t_mtok			*mtok_requal(t_mtok *mtk)
{
	t_mtok		**ok;
	t_mtok		*tmp;
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
			mtok_filen(tmp, ok, &filen);
		else if (tmp->type == DIREC)
			mtok_direc(tmp, ok, &filen);
	}
	return (ok[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 20:05:44 by lportay           #+#    #+#             */
/*   Updated: 2018/03/23 12:03:16 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	get_state(t_line *l)
{
	if (l->eohdoc)
		query_hdocstate(l->line, &l->linestate, l->eohdoc);
	else
		query_linestate(l->line->next, &l->linestate);
}

void	query_linestate(t_dlist *line, t_stack **linestate)
{
	if ((*linestate)->state == BSLASH)
		stack_pop(linestate);
	while (line && (*linestate)->state != HASH)
	{
		update_linestate(linestate, *(char *)(line->data));
		if (*(char *)(line->data) != '\\' && (*linestate)->state == BSLASH)
			stack_pop(linestate);
		line = line->next;
	}
	if ((*linestate)->state & HASH)
		stack_pop(linestate);
}

void	query_hdocstate(t_dlist *line, t_stack **linestate, char *eof)
{
	char *s;

	if (!(s = str_from_dlst(line)))
		return ;
	if (!ft_strcmp(s, eof))
	{
		stack_pop(linestate);
		ft_dlstdel(&line->next, &delvoid);
	}
	free(s);
}

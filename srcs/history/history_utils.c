/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:11:22 by lportay           #+#    #+#             */
/*   Updated: 2018/03/06 17:30:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	add_histfile(t_ctx *ctx)
{
	char	*filename;

	filename = NULL;
	if ((filename = ft_astr_getval(ctx->environ, "HOME")))
	{
		ft_astr_append(&ctx->locals, ft_strjoinc("HISTFILE", filename = ft_strjoinc(filename, HISTFILE, '/'), '='));
		free(filename);
	}
	else
		ft_astr_append(&ctx->locals, ft_strjoinc("HISTFILE", HISTFILE, '='));
}

char	*dump_history(t_dlist *histlist, int n)
{
	t_qbuf *buf;
	t_dlist *tmp;

	ft_dlstend(&histlist);
	buf = qbuf_new(256);
	qbuf_addc(buf, '1');
	while (histlist->prev && n)
	{
		qbuf_addl(buf, T_HISTENTRY(histlist->data)->index);
		qbuf_add(buf, "  ");
	
		tmp = T_HISTENTRY(histlist->data)->line->next;
		while (tmp)
		{
			qbuf_addc(buf, *(char *)tmp->data);
			tmp = tmp->next;
		}
		qbuf_addc(buf, '\n');

		histlist = histlist->prev;
		n--;
	}
	return (qbuf_del(&buf));
}

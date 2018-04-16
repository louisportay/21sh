/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:11:22 by lportay           #+#    #+#             */
/*   Updated: 2018/03/31 16:04:19 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	add_histfile(t_ctx *ctx)
{
	char	*filename;

	filename = NULL;
	if ((filename = ft_astr_getval(ctx->environ, "HOME")))
	{
		ft_astr_append(&ctx->locals, ft_strjoinc("HISTFILE",
					filename = ft_strjoinc(filename, HISTFILE, '/'), '='));
		free(filename);
	}
	else
		ft_astr_append(&ctx->locals, ft_strjoinc("HISTFILE", HISTFILE, '='));
}

char	*dump_history(t_dlist *histlist, int n)
{
	t_qbuf	*buf;
	t_dlist	*tmp;

	if (!n)
		return (NULL);
	while (--n > 0 && histlist->next)
		histlist = histlist->next;
	buf = qbuf_new(256);
	while (histlist->prev)
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

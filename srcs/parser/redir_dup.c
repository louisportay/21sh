/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 11:30:27 by lportay           #+#    #+#             */
/*   Updated: 2018/04/10 11:42:34 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	if (ft_strchr(r->s_rhs, '\\') || ft_strchr(r->s_rhs, '\'') ||
** ft_strchr(r->s_rhs, '"'))
**		r->glob = 0;
**	else
**		r->glob = 1;
** quote removal on r->s_rhs
**
** after getting the heredoc,
** apply expansion on r->s_rhs depending on r->glob
*/

void				get_hdoc_line(t_heredoc *r)
{
	r->hdoc.eohdoc = r->s_rhs;
	ft_readline(get_ctxaddr(), &r->hdoc, PS2);
	r->hdoc.eohdoc = NULL;
	ft_strdel(&r->s_rhs);
	if (r->hdoc.split_line &&
		(r->s_rhs = str_from_dlst(r->hdoc.split_line)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	if (r->hdoc.split_line)
		ft_dlstdel(&r->hdoc.split_line, &delvoid);
}

static inline void	*free_rdr(t_redir *rdr)
{
	free(rdr);
	return (NULL);
}

t_redir				*redir_dup(t_redir *redir)
{
	t_redir				*rdr;

	if (redir->type != DLESS)
		rdr = (t_redir *)ft_pmemalloc(sizeof(t_redir), &on_emem, NOMEM);
	else
		rdr = (t_redir *)ft_pmemalloc(sizeof(t_heredoc), &on_emem, NOMEM);
	rdr->type = redir->type;
	if ((rdr->s_rhs = ft_strdup(redir->s_rhs)) == NULL)
	{
		on_emem(NOMEM);
		return (NULL);
	}
	rdr->lhs = redir->lhs;
	if (rdr->type == DLESS)
	{
		get_hdoc_line((t_heredoc *)rdr);
		if (rdr->s_rhs == NULL)
			return (free_rdr(rdr));
	}
	else
	{
		rdr->fd_rhs = redir->fd_rhs;
		rdr->dash = redir->dash;
	}
	return (rdr);
}

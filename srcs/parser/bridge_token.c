/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:41:06 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/11 13:15:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					token_insert(t_token **head, t_token **curr, t_token *e)
{
	e->next = NULL;
	if (*head == NULL)
		*head = e;
	else
		(*curr)->next = e;
	*curr = e;
}

size_t					token_count(t_token *tok)
{
	size_t				len;

	len = 0;
	while (tok != NULL)
	{
		len++;
		tok = tok->next;
	}
	return (len);
}

t_redir					*redir_dup(t_redir *redir)
{
	t_redir				*rdr;

	rdr = (t_redir *)ft_pmemalloc(sizeof(t_redir), &on_emem, NOMEM);
	rdr->type = redir->type;
	if ((rdr->s_rhs = ft_strdup(redir->s_rhs)) == NULL)
	{
		on_emem(NOMEM);
		return (NULL);
	}
	rdr->lhs = redir->lhs;
	rdr->fd_rhs = redir->fd_rhs;
	rdr->dash = redir->dash;
	return (rdr);
}

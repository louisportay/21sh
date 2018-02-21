/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:41:06 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/16 10:04:17 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define FMT_SYN ("21sh: syntax error near unexpected token %s\n")
#define FMT_EOF ("EOF")
#define FMT_AND ("&")
#define FMT_SEM (";")
#define FMT_COM ("#")
#define FMT_OR ("|")
#define FMT_ORI ("||")
#define FMT_ANI ("&&")

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
	if (rdr->type != DLESS)
	{
		rdr->fd_rhs = redir->fd_rhs;
		rdr->dash = redir->dash;
	}
	return (rdr);
}

int						token_issep(t_token *tok)
{
	return ((tok->type & (NEWLINE | AND | SEMICOL | COMMENT | OR | OR_IF
							| AND_IF)) != 0);
}

void					*token_dumperror(t_token *tok)
{
	if (tok == NULL || tok->type == NEWLINE)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_EOF);
	else if (tok->type == AND)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_AND);
	else if (tok->type == SEMICOL)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_SEM);
	else if (tok->type == COMMENT)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_COM);
	else if (tok->type == OR)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_OR);
	else if (tok->type == OR_IF)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_ORI);
	else if (tok->type == AND_IF)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_ANI);
	return (NULL);
}

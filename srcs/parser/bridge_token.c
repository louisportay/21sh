/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:41:06 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/16 14:15:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

#define FMT_SYN ("42sh: syntax error near unexpected token %s\n")
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

int						token_issep(t_token *tok)
{
	return ((tok->type & (NEWLINE | AND | SEMICOL | OR | OR_IF
							| AND_IF)) != 0);
}

void					*token_dumperror(t_token *tok)
{
	if (tok == NULL || tok->type == NEWLINE)
		ft_dprintf(STDERR_FILENO, FMT_SYN, FMT_EOF);
	else if (tok->type == AND)
		ft_dprintf(STDERR_FILENO, FMT_SYN, FMT_AND);
	else if (tok->type == SEMICOL)
		ft_dprintf(STDERR_FILENO, FMT_SYN, FMT_SEM);
	else if (tok->type == OR)
		ft_dprintf(STDERR_FILENO, FMT_SYN, FMT_OR);
	else if (tok->type == OR_IF)
		ft_dprintf(STDERR_FILENO, FMT_SYN, FMT_ORI);
	else if (tok->type == AND_IF)
		ft_dprintf(STDERR_FILENO, FMT_SYN, FMT_ANI);
	return (NULL);
}

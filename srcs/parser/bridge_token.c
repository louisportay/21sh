/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:41:06 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/10 18:27:05 by vbastion         ###   ########.fr       */
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

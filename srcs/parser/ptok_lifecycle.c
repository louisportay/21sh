/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptok_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:30 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/11 19:53:55 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				ptok_free(t_ptok **tok)
{
	*tok = NULL;
	return ;
}

void				ptok_insert(t_ptok **head, t_ptok **curr, t_ptok *e)
{
	if (*head == NULL)
		*head = e;
	else
		(*curr)->next = e;
	*curr = e;
}

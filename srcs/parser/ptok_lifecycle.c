/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptok_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:30 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/10 13:19:01 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_ptok				*ptok_new(void)
{
	t_ptok			*ptok;

	if ((ptok = (t_ptok *)ft_memalloc(sizeof(t_ptok))) == NULL)
	{
		fatal_err(NOMEM, get_ctxaddr(NULL));
		return (NULL);
	}
	return (ptok);
}

void				ptok_free(t_ptok **tok)
{
	*tok = NULL;
	return ;
}

void				ptok_clear(t_ptok **tokens)
{
	*tokens = NULL;
	return ;
}

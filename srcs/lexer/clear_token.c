/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 20:57:56 by lportay           #+#    #+#             */
/*   Updated: 2018/03/18 15:11:55 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	clear_following_redirs(t_token *toklist)
{
	while (toklist)
	{
		if (toklist->type & RDIR)
			toklist->type = WORD;
		toklist = toklist->next;
	}
}

void	delete_toklist(t_token **toklist)
{
	t_token *tmp;

	tmp = *toklist;
	while (tmp)
	{
		*toklist = (*toklist)->next;
		if (tmp->type & RDIR)
			free(((t_redir *)tmp)->s_rhs);
		free(tmp);
		tmp = *toklist;
	}
	*toklist = NULL;
}

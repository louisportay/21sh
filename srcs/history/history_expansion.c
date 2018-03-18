/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:24:04 by lportay           #+#    #+#             */
/*   Updated: 2018/03/17 21:14:47 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_21sh.h"

t_dlist 	*munch_string(t_dlist *line)
{
	while (line->next && !is_metachar(*(char *)line->next->data) && !ft_isblank(*(char *)line->next->data))
		line = line->next;
	return (line);
}

t_dlist		*munch_number(t_dlist *line)
{
	if (*(char *)line->next->data == '-')
		line = line->next;
	while (line->next && ft_isdigit(*(char *)line->next->data))
			line = line->next;
	return (line);
}

t_dlist		*expand_bang(t_hist *hist, t_dlist *line)
{
	t_dlist		*end;
//	unsigned	index;
	(void)hist;//

	if (!line->next || ft_isblank(*(char *)line->next->data) ||
	*(char *)line->next->data == '\n' || *(char *)line->next->data == '\r' ||
	*(char *)line->next->data == '=')
		return (line);
	if (ft_isdigit(*(char *)line->next->data) ||
(line->next->next && *(char *)line->next->data == '-' && ft_isdigit(*(char *)line->next->next->data)))
		end = munch_number(line->next);
	else if (*(char *)line->next->data == '!')
	{
		end = line->next;

		line->prev->next = end->next;
		line->prev = NULL;
		end->next = NULL;

//		ft_dlstdel(line
		return (line->next);
	}
	else
		end = munch_string(line);

	line->prev->next = end->next;
	line->prev = NULL;
	end->next = NULL;
	if (!line->next)
		return (NULL);//
		//printf("\n%s\n", dlst_to_str(line));
	return (line->next);//
}

void	history_expansion(t_hist *hist, t_dlist *line)
{
	while (line->next)
	{
		//verifier le quoting de l'histoire
		if (*(char *)line->data == '!')
			line = expand_bang(hist, line);
		else
			line = line->next;
	}
}

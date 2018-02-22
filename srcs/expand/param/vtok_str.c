/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:59:10 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/22 14:00:11 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

int					vtok_counttil(t_vtok *head, enum e_vtype type)
{
	int				n;

	n = 0;
	while (head->type != type)
	{
		n++;
		head = head->next;
	}
	return (n);
}

t_vtok				*vtok_getclose(t_vtok *tok)
{
	int				depth;

	depth = 0;
	while (tok != NULL)
	{
		if (tok->type == VADOLL && vtok_assert(tok, 1, VAOBRA))
			depth++;
		if (tok->type == VACBRA)
		{
			if (depth == 0)
				return (tok->next);
			else
				depth--;
		}
		tok = tok->next;
	}
	return (NULL);
}

void				vtok_splittilclose(t_vtok *tok, t_vtok **next)
{
	int				depth;
	t_vtok			*prev;

	depth = 0;
	prev = NULL;
	while (tok != NULL)
	{
		if (tok->type == VADOLL && vtok_peek_if(tok, 1, VAOBRA) != NULL)
			depth++;
		else if (tok->type == VACBRA)
		{
			if (depth == 0)
				break ;
			else
				depth--;
		}
		prev = tok;
		tok = tok->next;
	}
	if (prev != NULL)
		prev->next = NULL;
	*next = tok;
}

int					vtok_isword(char *str)
{
	if (ft_isalpha(*(str++)) == 0)
		return (0);
	while (*str != '\0')
	{
		if (ft_isalnum(*(str++)) == 0)
			return (0);
	}
	return (1);
}

t_vtok				*vtok_last(t_vtok *last)
{
	if (last == NULL)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

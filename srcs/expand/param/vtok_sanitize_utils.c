/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_san_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:14:43 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 20:24:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

int						vtok_isopen(t_vtok *curr)
{
	return (curr->type == VADOLL && vtok_assert(curr, 1, VAOBRA));
}

void					vtok_conv(t_vtok *curr)
{
	curr->type = VOTHER;
	curr->data.str = ft_strdup("$");
	curr->next->type = VOTHER;
	curr->next->data.str = ft_strdup("{");
}

void					vtok_split(t_vtok *tok, enum e_vtype type,
									t_vtok **next)
{
	t_vtok				*prev;

	prev = NULL;
	while (tok != NULL)
	{
		if (tok->type == type)
		{
			if (prev != NULL)
				prev->next = NULL;
			*next = tok;
			return ;
		}
		prev = tok;
		tok = tok->next;
	}
}

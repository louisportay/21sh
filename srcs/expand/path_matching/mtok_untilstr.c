/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_untilstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:28:35 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/05 15:31:47 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

int				mtok_until_str(t_mtok *tok, char *str, t_mtok **next)
{
	*next = NULL;
	while (tok->next != NULL)
	{
		if (tok->next->type == STRIN
			&& ft_strcmp(tok->next->data.str, str) == 0)
		{
			*next = tok->next;
			tok->next = NULL;
			return (1);
		}
		tok = tok->next;
	}
	return (0);
}

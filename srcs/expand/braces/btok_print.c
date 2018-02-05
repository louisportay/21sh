/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btok_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 17:31:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/13 15:10:23 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

void				btok_print(t_btok *tok)
{
	while (tok != NULL)
	{
		btok_printone(tok);
		tok = tok->next;
	}
}

void				btok_printone(t_btok *tok)
{
	if (tok->type == BROBRA)
		ft_putstr("BROBRA");
	if (tok->type == BRCBRA)
		ft_putstr("BRCBRA");
	if (tok->type == BCOMMA)
		ft_putstr("BCOMMA");
	if (tok->type == BPOINT)
		ft_putstr("BPOINT");
	if (tok->type == BRDOLL)
		ft_putstr("BRDOLL");
	if (tok->type == BOTHER)
		ft_putstr("BOTHER");
	ft_putstr(" - ");
	ft_putendl(tok->val);
}

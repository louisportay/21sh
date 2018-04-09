/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:31:19 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/08 19:20:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

void			vtok_print(t_vtok *tok)
{
	while (tok != NULL)
	{
		vtok_printone(tok);
		tok = tok->next;
	}
}

void			vtok_printone(t_vtok *tok)
{
	if (tok->type == VADOLL)
		ft_putendl("VADOLL");
	if (tok->type == VAOBRA)
		ft_putendl("VAOBRA");
	if (tok->type == VACBRA)
		ft_putendl("VACBRA");
	if (tok->type == VSPACE)
		ft_putendl("VSPACE");
	if (tok->type == VDQUOT)
		ft_putendl("VDQUOTE");
	if (tok->type == VAWORD)
		ft_putendl("VAWORD");
	if (tok->type == VOTHER)
		ft_putendl("VOTHER");
	if (tok->type == VUNDER)
		ft_putendl("VUNDER");
	if (tok->type == VQUEST)
		ft_putendl("VQUEST");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:03:23 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/07 13:40:13 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

void			mtok_print(t_mtok *o)
{
	while (o != NULL)
	{
		if (o->type == STRIN)
		{
			ft_putstr("STRIN: ");
			ft_putendl(o->data.str);
		}
		else if (o->type == DIREC)
			ft_putstr("DIREC\n");
		else if (o->type == FILEN)
			ft_putstr("FILEN\n");
		else if (o->type == RECUR)
			ft_putstr("RECUR\n");
		else if (o->type == ANYSI)
			ft_putstr("ANYSI\n");
		else if (o->type == RANGE)
		{
			ft_putstr("RANGE: ");
			ft_putendl(o->data.str);
		}
		else if (o->type == RNMOD)
			ft_putstr("RNMOD\n");
		o = o->next;
	}
}

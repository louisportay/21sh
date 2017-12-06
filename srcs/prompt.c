/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 19:18:10 by lportay           #+#    #+#             */
/*   Updated: 2017/12/06 21:47:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//imprimer le bon prompt en fonction du mode (state)
//faire un tableau d'association pour le mode et la variable a chercher

void	print_prompt(t_21sh *env)
{
	t_hash *ps1;

	if ((ps1 = hashlookup(env->localvar, "PS1")))
	{
		change_cursor_offset(env, ft_strlen((char *)ps1->data));
		ft_putstr((char *)ps1->data);//remplacer ca par une fonction qui expand vraiment le prompt a la bash
	}
}

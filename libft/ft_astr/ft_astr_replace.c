/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 18:51:18 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/14 18:53:05 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

void				ft_astr_replace(char **astr, int i, char *new_val)
{
	ft_strdel(astr + i);
	astr[i] = new_val;
}

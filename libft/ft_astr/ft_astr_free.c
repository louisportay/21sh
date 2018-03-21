/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:02:03 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/21 10:29:56 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

void			ft_astr_nfree(char **astr, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		ft_strdel(astr + i);
		i++;
	}
}

void			ft_astr_free(char ***astr)
{
	size_t		i;

	if (*astr == NULL)
		return ;
	i = 0;
	while ((*astr)[i] != NULL)
	{
		ft_strdel((*astr) + i);
		i++;
	}
	ft_memdel((void **)astr);
}

int				ft_astr_clear(char ***astr)
{
	char		**c;

	if (astr == NULL || *astr == NULL)
		return (1);
	c = *astr;
	while (*c != NULL)
	{
		ft_strdel(c);
		c++;
	}
	ft_memdel((void **)astr);
	return (1);
}

int				ft_astr_nclear(char **astr, size_t n, void **head)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		ft_strdel(astr + i);
		i++;
	}
	ft_memdel(head);
	return (1);
}

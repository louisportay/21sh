/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttok_combine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:12:50 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/13 15:16:06 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

static int			l_inc_numrng(t_ttok *tok)
{
	union u_tdata	*data;

	data = &tok->data;
	if (data->rng[2] == data->rng[1])
	{
		data->rng[2] = data->rng[0];
		return (0);
	}
	if (data->rng[0] < data->rng[1])
		data->rng[2]++;
	else
		data->rng[2]--;
	return (1);
}

static int			l_inc_alprng(t_ttok *tok)
{
	union u_tdata	*data;

	data = &tok->data;
	if (data->rng[2] == data->rng[1])
	{
		data->rng[2] = data->rng[0];
		return (0);
	}
	if (data->rng[0] < data->rng[1])
		data->rng[2]++;
	else
		data->rng[2]--;
	return (1);
}

static int			l_inc_mixrng(t_ttok *tok)
{
	union u_tdata	*data;

	data = &tok->data;
	if (data->elem[1]->next == NULL)
	{
		data->elem[1] = data->elem[0];
		return (0);
	}
	data->elem[1] = data->elem[1]->next;
	return (1);
}

int					ttok_iter(t_ttok *tok)
{
	if (tok == NULL)
		return (0);
	if (tok->type == TSTRING)
		return (ttok_iter(tok->next));
	if (ttok_iter(tok->next) == 1)
		return (1);
	if (tok->type == TNUMRNG)
		return (l_inc_numrng(tok));
	else if (tok->type == TALPRNG)
		return (l_inc_alprng(tok));
	else
		return (l_inc_mixrng(tok));
}

char				*ttok_combine(t_ttok *tok)
{
	t_ttok			*elem[3];
	char			*ret;

	elem[0] = NULL;
	while (1)
	{
		if ((elem[2] = ttok_comb(tok)) == NULL)
		{
			ttok_clear(elem);
			return (NULL);
		}
		ttok_insert(elem, elem + 1, elem[2]);
		if (ttok_iter(tok) == 0)
			break ;
	}
	ret = (ttok_tostr(elem[0]));
	ttok_clear(elem);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttok_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 15:15:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/13 15:19:53 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

char				*ttok_tostr(t_ttok *tok)
{
	t_qbuf			*buf;

	buf = qbuf_new(128);
	while (tok != NULL)
	{
		qbuf_add(buf, tok->data.str);
		tok = tok->next;
		if (tok != NULL)
			qbuf_addc(buf, ' ');
	}
	return (qbuf_del(&buf));
}

void				ttok_printone(t_ttok *tok)
{
	t_list			*l;

	if (tok->type == TNUMRNG)
		ft_putendl("TNUMRNG");
	else if (tok->type == TALPRNG)
		ft_putendl("TALPRNG");
	else if (tok->type == TMIXRNG)
	{
		ft_putstr("TALPRNG:\n");
		l = tok->data.elem[0];
		while (l != NULL)
		{
			ft_putstr("\telem: ");
			ft_putendl((char *)l->content);
			l = l->next;
		}
	}
	else
	{
		ft_putstr("TSTRING: ");
		ft_putendl(tok->data.str);
	}
}

void				ttok_print(t_ttok *toks)
{
	while (toks != NULL)
	{
		ttok_printone(toks);
		toks = toks->next;
	}
}

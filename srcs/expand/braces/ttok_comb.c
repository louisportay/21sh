/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttok_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:43:12 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/11 17:58:01 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

t_ttok				*ttok_comb(t_ttok *tok)
{
	t_qbuf			*buf;
	char			b[20];

	buf = qbuf_new(128);
	while (tok != NULL)
	{
		if (tok->type == TSTRING)
			qbuf_add(buf, tok->data.str);
		else if (tok->type == TALPRNG)
			qbuf_addc(buf, tok->data.rng[2]);
		else if (tok->type == TMIXRNG)
			qbuf_add(buf, (char *)tok->data.elem[1]->content);
		else
		{
			ft_bzero(b, 20);
			ft_ltobuf((long long)tok->data.rng[2], 10, 0, b);
			qbuf_add(buf, b);
		}
		tok = tok->next;
	}
	return (ttok_newstr(qbuf_del(&buf)));
}

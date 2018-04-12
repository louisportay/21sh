/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttok_compose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:54:58 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/11 19:10:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

static t_ttok		*l_tosrange(t_btok **head)
{
	char			*str[2];
	int				*n;
	t_ttok			*ret;
	u_char			c;

	str[0] = btok_peek((*head), 1)->val;
	str[1] = btok_peek((*head), 4)->val;
	c = 0;
	if (ft_isnumber(str[0]) && ft_isnumber(str[1]))
	{
		n = (int[]){ ft_atoi(str[0]), ft_atoi(str[1])};
		c = 1;
	}
	else if (ft_islet(str[0]) && ft_islet(str[1]))
	{
		n = (int[]){ str[0][0], str[1][0] };
		c = 2;
	}
	else
		return (ttok_flatten(head));
	ret = ttok_newrng(c == 1 ? TNUMRNG : TALPRNG, n[0], n[1]);
	*head = btok_peek((*head), 6);
	return (ret);
}

t_ttok				*ttok_compose(t_btok **btok)
{
	t_btok			*n;

	n = (*btok)->next;
	if (btok_match(n, (int[]){BOTHER, BPOINT, BPOINT, BOTHER, BRCBRA, -1}))
		return (l_tosrange(btok));
	return (ttok_do_mix(btok));
}

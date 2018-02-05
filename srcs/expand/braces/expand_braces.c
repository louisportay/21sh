/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_braces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:46:39 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/14 11:40:23 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

int					expand_braces(char **str)
{
	char			*s;
	t_btok			*tok;
	t_ttok			*ttok;
	char			*ret;

	s = *str;
	if (braces_scan(s) == 0)
		return (1);
	tok = btok_get(s);
	btok_sanitize(tok);
	ttok = ttok_get(tok);
	btok_clear(&tok);
	ret = ttok_combine(ttok);
	ttok_clear(&ttok);
	if (ret != NULL)
	{
		ft_strdel(str);
		*str = ret;
		return (1);
	}
	ft_putendl_fd("Could not allocate memory", STDERR_FILENO);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_braces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:46:39 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 14:56:20 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"
#include "builtins.h"

int					expand_braces(char *str, char **ret)
{
	t_btok			*tok;
	t_ttok			*ttok;
	int				r;
	int				err;

	if ((get_ctxaddr()->set & BRACE_EXPAND) == 0)
		return (0);
	if ((r = braces_scan(str)) == 0)
		return (0);
	else if (r == -1)
		return (-1);
	*ret = NULL;
	err = 0;
	if ((tok = btok_get(str, &err)) == NULL)
		return (err ? -3 : -1);
	btok_sanitize(tok);
	ttok = ttok_get(tok);
	btok_clear(&tok);
	*ret = ttok_combine(ttok);
	ttok_clear(&ttok);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_braces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:46:39 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 12:48:08 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

int					expand_braces(char *str, char **ret)
{
	t_btok			*tok;
	t_ttok			*ttok;

	if (braces_scan(str) == 0)
		return (0);
	*ret = NULL;
	tok = btok_get(str);
	btok_sanitize(tok);
	ttok = ttok_get(tok);
	btok_clear(&tok);
	*ret = ttok_combine(ttok);
	ttok_clear(&ttok);
	return (1);
}

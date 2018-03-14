/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_go_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:55:56 by lportay           #+#    #+#             */
/*   Updated: 2018/03/14 13:55:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

bool	test_upper_line(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)ctx;
	if (!ft_strncmp(key->buf, C_UP, ft_strlen(C_UP)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->cursor_line != 0)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_lower_line(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)ctx;
	if (!ft_strncmp(key->buf, C_DOWN, ft_strlen(C_DOWN)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->cursor_line < l->num_lines)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

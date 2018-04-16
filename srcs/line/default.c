/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 19:20:03 by lportay           #+#    #+#             */
/*   Updated: 2018/04/09 14:19:37 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	reset_attributes(t_line *l)
{
	print_prompt();
	l->cursor_line = l->num_lines;
	l->offset_inline = l->prompt_len;
}

void	init_line(t_line *l)
{
	if ((l->line = ft_dlstnew("HEAD", 4)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	l->lastline = l->line;
	reset_attributes(l);
}

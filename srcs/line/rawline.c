/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rawline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:26:30 by lportay           #+#    #+#             */
/*   Updated: 2018/03/30 16:24:31 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Called when:
** 				-line editing mode not available (missing termcap, whatever...)
**				-When the input is not a Terminal
*/

void	getrawline(t_ctx *ctx, t_line *l)
{
	char *tmp;

	print_prompt();
	if (get_next_line(ctx->fd, &tmp) == -1)
		fatal_err(FAILREAD, ctx);
	if (!tmp && l->linestate->state == UNQUOTED)
		wrap_exit(EXIT_SUCCESS, ctx);
	else if (!tmp && l->eohdoc)
		return (warning_heredoc(l));
	else if (!tmp)
		return (err_line(l, BADQUOTES));
	if (l->eohdoc && !l->linestate->down)
	{
		free(tmp);
		return ;
	}
	l->line = dlst_from_str(tmp);
	get_state(l);
	if (l->linestate->state != UNQUOTED)
		ft_strcpy(ctx->prompt_mode, PS2);
	join_split_lines(l);
	add_newline(l);
	free(tmp);
	l->line = NULL;
}

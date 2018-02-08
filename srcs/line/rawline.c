/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rawline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:26:30 by lportay           #+#    #+#             */
/*   Updated: 2018/02/07 18:27:21 by lportay          ###   ########.fr       */
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

	print_prompt(ctx);
	if (get_next_line(STDIN_FILENO, &tmp) == -1)
		fatal_err(FAILREAD, ctx);
	if (!tmp && ctx->line.linestate->state == UNQUOTED)
		wrap_exit(EXIT_SUCCESS, ctx);
	else if (!tmp)
		return (err_quotes(l));
	l->line = str_to_dlst(tmp);

	query_linestate(l->line->next, &l->linestate);
//ajouter la gestion pour le heredoc
	if (l->linestate->state != UNQUOTED)
		ft_strcpy(ctx->prompt_mode, PS2);
	join_split_lines(l);
	if (l->linestate->state == UNQUOTED || l->linestate->state == SQUOTE || l->linestate->state == DQUOTE)
		ft_dlstaddend(l->split_line, (l->final_newline = ft_dlstnew(ft_strdup("\n"))));

	free(tmp);
	l->line = NULL;
}

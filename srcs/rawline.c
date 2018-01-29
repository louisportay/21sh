/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rawline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:26:30 by lportay           #+#    #+#             */
/*   Updated: 2018/01/28 19:39:47 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Called when:
** 				-line editing mode not available (missing termcap, whatever...)
**				-When the input is not a Terminal
*/

static void	getrawline(t_21sh *env, t_line *line)
{
	char *tmp;

	print_prompt(env);
	if (line->linestate->state == BSLASH)
		stack_pop(&line->linestate);
	if (get_next_line(STDIN_FILENO, &tmp) == -1)
		fatal_err(FAILREAD, env);
	if (!tmp && env->line.linestate->state == UNQUOTED)
		wrap_exit(EXIT_SUCCESS, env);
	else if (!tmp)
		return (err_quotes(line));
	line->line = str_to_dlst(tmp);

	query_linestate(line->line->next, &line->linestate);
	if (line->linestate->state == HASH)
		stack_pop(&line->linestate);
	if (line->linestate->state != UNQUOTED)
		ft_strcpy(env->prompt_mode, PS2);
	join_split_lines(line);
	if (line->linestate->state == UNQUOTED || line->linestate->state == SQUOTE || line->linestate->state == DQUOTE)
		ft_dlstaddend(line->split_line, (line->final_newline = ft_dlstnew("\n", 1)));

	free(tmp);
	line->line = NULL;
}

void	wrap_getrawline(t_21sh *env)
{
		getrawline(env, &env->line);
		while (env->line.linestate && env->line.linestate->state != UNQUOTED)
			getrawline(env, &env->line);
}


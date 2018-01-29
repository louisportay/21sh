/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 18:33:51 by lportay           #+#    #+#             */
/*   Updated: 2018/01/28 19:36:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		lineread(t_21sh *env, t_line *line)
{
	int		status;
	char	buf[READLEN];
	int		bufi;

	bufi = 0;
	status = READON;
	line->line = ft_dlstnew("HEAD", 5);
	line->lastline = line->line;
	line->cursor_offset = 0;
	line->multiline = false;
	print_prompt(env);
	line->line_len = line->cursor_offset;
	ft_bzero(buf, READLEN);
	if (line->linestate->state == BSLASH)
		stack_pop(&line->linestate);

	tputs(line->tc.im, 1, &ft_putchar_stdin);
	while (status == READON)
	{
		if (read(STDIN_FILENO, &buf[bufi++], 1) == -1)
			status = READERROR;
		else
			status = user_input(env, buf, &bufi);
	}
	tputs(line->tc.ei, 1, &ft_putchar_stdin);

	if (line->multiline == true)
		move_cursor_end_of_line(env);
	if (env->hist.list)
		ft_dlsthead(&env->hist.list);
	ft_dlsthead(&line->line);
	if (status == READERROR)
		fatal_err(FAILREAD, env);
	else if (status == EXITSHELL)
		wrap_exit(EXIT_SUCCESS, env);
	else if (status == ERR_QUOTE)
		return (err_quotes(line));

	query_linestate(line->line->next, &line->linestate);

	if (line->linestate->state == HASH)
		stack_pop(&line->linestate);

	if (line->linestate->state != UNQUOTED)
	{
		if ((line->cursor_offset % env->line.ws.ws_col))
			write(STDIN_FILENO, "\n", 1);
		ft_strcpy(env->prompt_mode, PS2);
	}

	join_split_lines(line);

	if (env->history && line->split_line->next && line->linestate->state == UNQUOTED && dlst_isblank(line->split_line->next) == false)
	{
		add_histentry(env);
		line->line_saved = true;
	}

	if (line->linestate->state == UNQUOTED || line->linestate->state == SQUOTE || line->linestate->state == DQUOTE)
		ft_dlstaddend(line->split_line, (line->final_newline = ft_dlstnew("\n", 1)));
}

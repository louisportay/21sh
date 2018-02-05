/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 18:33:51 by lportay           #+#    #+#             */
/*   Updated: 2018/02/05 23:02:25 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"


void	init_line(t_21sh *env, t_line *line, t_key *key, int *status)
{
	ft_bzero(key->buf, READLEN);
	key->i = 0;
	*status = READON;
	line->line = ft_dlstnew("HEAD", 5);
	line->lastline = line->line;
	line->cursor_offset = 0;
	line->multiline = false;
	print_prompt(env);
	line->line_len = line->cursor_offset;
}

void		lineread(t_21sh *env, t_line *line)
{
	t_key	key;
	int		status;

	init_line(env, line, &key, &status);	
	
	env->cur_line = line;
	tputs(env->tc.im, 1, &ft_putchar_stdin);
	while (status == READON)
	{
		if (read(STDIN_FILENO, &key.buf[key.i++], 1) == -1)
			status = READERROR;
		else
			status = user_input(env, line, &key);
	}
	tputs(env->tc.ei, 1, &ft_putchar_stdin);
	env->cur_line = NULL;	

	if (line->multiline == true)
		move_cursor_end_of_line(env, line);
	if (env->hist.list)
		ft_dlsthead(&env->hist.list);
	ft_dlsthead(&line->line);

	if (status == READERROR)
		fatal_err(FAILREAD, env);
	else if (status == EXITSHELL)
		wrap_exit(EXIT_SUCCESS, env);
	else if (status == ERR_QUOTE)
		return (err_quotes(line));

	if (env->heredoc_eof)
		query_hdocstate(line->line->next, &line->linestate, env->heredoc_eof);
	else
		query_linestate(line->line->next, &line->linestate);
	if (line->linestate->state != UNQUOTED)
	{
		ft_strcpy(env->prompt_mode, PS2);
		if ((line->cursor_offset % env->ws.ws_col))
			write(STDOUT_FILENO, "\n", 1);
	}
	else
		write(STDOUT_FILENO, "\n", 1);

	join_split_lines(line);

	if (env->history && line->split_line->next && line->linestate->state == UNQUOTED && !dlst_isblank(line->split_line->next) && !env->heredoc_eof)
	{
		add_histentry(env);
		line->line_saved = true;
	}

	if (line->linestate->state == UNQUOTED || line->linestate->state == SQUOTE || line->linestate->state == DQUOTE)
		ft_dlstaddend(line->split_line, (line->final_newline = ft_dlstnew("\n", 1)));
}

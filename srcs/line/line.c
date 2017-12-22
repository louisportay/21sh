/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2017/12/22 10:29:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	init_funcs(t_line_func *funcs)
{
	funcs[0] = LINE_FUNC(&test_upkey, &up_key);
	funcs[1] = LINE_FUNC(&test_downkey, &down_key);
	funcs[2] = LINE_FUNC(&test_lkey, &lkey);
	funcs[3] = LINE_FUNC(&test_rkey, &rkey);
	funcs[4] = LINE_FUNC(&test_del_current_char, &del_current_char);
	funcs[5] = LINE_FUNC(&test_del_previous_char, &del_previous_char);
	funcs[6] = LINE_FUNC(&test_line_beginning, &go_to_line_beginning);
	funcs[7] = LINE_FUNC(&test_line_end, &go_to_line_end);
	funcs[8] = LINE_FUNC(&test_lower_line, &go_lower_line);
	funcs[9] = LINE_FUNC(&test_upper_line, &go_upper_line);
	funcs[10] = LINE_FUNC(&test_previous_word, &go_to_previous_word);
	funcs[11] = LINE_FUNC(&test_next_word, &go_to_next_word);
	funcs[12] = LINE_FUNC(&test_kill_beginline, &kill_line_beginning);
	funcs[13] = LINE_FUNC(&test_kill_endline, &kill_line_end);
	funcs[14] = LINE_FUNC(&test_clear_screen, &clear_screen_);
	funcs[15] = LINE_FUNC(&test_yank, &yank);
	funcs[16] = LINE_FUNC(&test_emacs_mode, &reverse_emacs_mode);
	funcs[17] = LINE_FUNC(NULL, NULL);
}

static int	user_input(t_21sh *env, char *buf, int *bufi)
{
	t_line_func	funcs[18];
	int			i;

	i = 0;
	init_funcs(funcs);	
	update_linemode(env);
	if (test_load_line(env, buf) == true)
		load_line(env);
	if (*buf == NEWLINE_ || (env->emacs_mode && *buf == C_O))
	{
		if (env->line && ft_dlstaddr(env->line, 0) != env->lastline)
			ft_dlstdel(&env->lastline, &delvoid);
		return (FINISHREAD);
	}
	else if (*buf == C_D && !ft_dlstcount(env->line))
		return (EXITSHELL);
	else if (ft_isprint(*buf))
		insert_char(buf, env);
	else
	{
		while (funcs[i].test && funcs[i].test(env, buf, bufi) == false)
			i++;
		if (funcs[i].test)
			funcs[i].f(env);
	}
	if ((buf[0] && buf[0] != ESC) || (buf[1] && buf[1] != '[') || *bufi == READLEN)
	{
		ft_bzero(buf, *bufi);
		*bufi = 0;
	}

////	else if (buf == C_W && env->line->previous)
////		kill_prev_word(env);
////	else if (!ft_strncmp(buf, M_D, ft_strlen(M_D)) && env->line->next)
////		kill_next_word(env);

//	else if (buf == C_R && env->history)
//		recherche dans l'historique (C_G + C_J + C_O)
//	else if (buf == TAB && env->autocomplete)
//		autocompletion
	return (READON);
}

//change lineread return *eventually*

void		lineread(t_21sh *env)
{
	int		status;
	char	buf[READLEN];
	int		bufi;

	bufi = 0;
	status = READON;
	env->line = ft_dlstnew("HEAD", 5);
	env->lastline = env->line;
	env->cursor_offset = 0;
	env->multiline = false;
	print_prompt(env);
	env->line_len = env->cursor_offset;
	ft_bzero(buf, READLEN);

	tputs(env->tc.im, 1, &ft_putchar_stdin);
	while (status == READON)
	{
		if (read(STDIN_FILENO, &buf[bufi++], 1) == -1)
			status = READERROR;
		else
			status = user_input(env, buf, &bufi);
	}
	tputs(env->tc.ei, 1, &ft_putchar_stdin);

	if (env->multiline == true)
		move_cursor_end_of_line(env);
	if (env->histlist)
		ft_dlsthead(&env->histlist);
	ft_dlsthead(&env->line);
	if (status == READERROR)
		fatal_err(FAILREAD, env);
	else if (status == EXITSHELL)
		wrap_exit(EXIT_SUCCESS, env);
	if (env->history)
		add_histentry(env);
	else 
		ft_dlstdel(&env->line, &delvoid);

//		return (EXIT_SUCCESS);
//	else if (status == FINISHREAD)
//		add_histentry(env);
//	 	return (FINISHREAD);
//	we're all done! add histentry and return

	//DEBUG//
	write(1, "\n", 1);//
	if (env->line)
		print_line(env->line->next);//print what's retrieved
	write(1, "\n", 1);//
	/////////

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsub_bquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:46:43 by lportay           #+#    #+#             */
/*   Updated: 2018/04/19 16:36:56 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_cmdsub.h"

int		match_bquotes(char *s, char **o_bquote)
{
	*o_bquote = s;
	while (*o_bquote && (*o_bquote = ft_strchr(*o_bquote, '`')) != NULL)
	{
		if (*o_bquote == s || *(*o_bquote - 1) != '\\')
			return (1);
		(*o_bquote)++;
	}
	return (0);
}

static t_dlist	*extract_cmd(char *opening_bquote, char **closing_bquote)
{
	t_dlist *cmd;
	char	*str_cmd;

	match_bquotes(&opening_bquote[1], closing_bquote);
	**closing_bquote = '\0';
	str_cmd = ft_strdup(&opening_bquote[1]);
	if (!str_cmd)
		fatal_err(NOMEM, get_ctxaddr());	
	**closing_bquote = '`';
	(*closing_bquote)++;
	cmd = dlst_from_str(str_cmd);
	if (cmd && ft_dlstnewaddend(cmd, "\n", 1, &ft_dlstnew) == -1)
		fatal_err(NOMEM, get_ctxaddr());
	free(str_cmd);
	return (cmd);
}

int		bquotes_exp(char *s, char *opening_bquote, char **new_s)
{
	t_qbuf	*qbuf;
	char	*c_bquote;
	t_dlist *cmd;
	int		fd[2];
	pid_t	pid;

	qbuf = qbuf_new(128);
	if (s != opening_bquote)
		qbuf_addn(qbuf, s, opening_bquote - s);		
	if ((cmd = extract_cmd(opening_bquote, &c_bquote)) == NULL)
		return (0);
	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (print_err("42sh: fork: could not fork\n", 0));
	else if (pid == 0)
		subshell(fd, cmd);
	else
		read_from_subshell(fd, c_bquote, qbuf);
	ft_dlstdel(&cmd, &delvoid);
	*new_s = qbuf_del(&qbuf);
	return (1);
}

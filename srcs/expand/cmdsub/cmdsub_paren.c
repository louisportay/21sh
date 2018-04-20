/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsub_paren.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:13:46 by lportay           #+#    #+#             */
/*   Updated: 2018/04/20 14:19:14 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_cmdsub.h"

/*
** U R not matching recursive parentheses
*/

int		match_paren(char *s, char **dollar_sign, char **closing_paren)
{
	*dollar_sign = s;
	while (*dollar_sign && (*dollar_sign = ft_strstr(*dollar_sign, "$(")) != NULL)
	{
		if ((*dollar_sign == s || *(*dollar_sign - 1) != '\\') &&
		(*closing_paren = ft_strchr(*dollar_sign, ')')) && *(*closing_paren - 1) != '\\')
				return (1);
		(*dollar_sign)++;
	}
	return (0);
}

static t_dlist	*extract_cmd(char *dollar, char **closing_paren)
{
	t_dlist *cmd;
	char	*str_cmd;

	**closing_paren = '\0';
	str_cmd = ft_strdup(&dollar[2]);
	if (!str_cmd)
		fatal_err(NOMEM, get_ctxaddr());	
	**closing_paren = ')';
	(*closing_paren)++;
	cmd = dlst_from_str(str_cmd);
	if (cmd && ft_dlstnewaddend(cmd, "\n", 1, &ft_dlstnew) == -1)
		fatal_err(NOMEM, get_ctxaddr());
	free(str_cmd);
	return (cmd);
}

int		paren_exp(char *s, char *dollar, char *c_paren, char **new_s)
{
	t_qbuf	*qbuf;
	t_dlist *cmd;
	int		fd[2];
	pid_t	pid;

	qbuf = qbuf_new(128);
	if (s != dollar)
		qbuf_addn(qbuf, s, dollar - s);		
	if ((cmd = extract_cmd(dollar, &c_paren)) == NULL)
		return (0);
	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (print_err("42sh: fork: could not fork\n", 0));
	else if (pid == 0)
		subshell(fd, cmd);
	else
		read_from_subshell(fd, c_paren, qbuf);
	ft_dlstdel(&cmd, &delvoid);
	*new_s = qbuf_del(&qbuf);
	return (1);
}

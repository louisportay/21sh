/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmdsub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:09:20 by lportay           #+#    #+#             */
/*   Updated: 2018/04/20 09:24:46 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_cmdsub.h"

void	remove_nl(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			*s = ' ';
		s++;
	}

}

void	subshell(int fd[2], t_dlist *cmd)
{
	t_ctx *ctx;

	ctx = get_ctxaddr();
	close(fd[0]);
	close(ctx->std_fd[1]);
	ctx->std_fd[0] = fd[0];
	ctx->std_fd[1] = fd[1];
	dup2(fd[1], STDOUT_FILENO);
	exec_loop(cmd);
	exit(0);
}

void	read_from_subshell(int fd[2], char *c_char, t_qbuf *qbuf)
{
	char	buf[BUFF_SIZE];
	size_t	sz;

	close(fd[1]);
	while ((sz = read(fd[0], buf, BUFF_SIZE)) != 0)
		qbuf_addn(qbuf, buf, sz);
	if (qbuf->buffer[0] != '"')
		remove_nl(qbuf->buffer);
	if (qbuf->used > 0)
		qbuf->used--;	
	qbuf_add(qbuf, c_char);
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

//U R not matching recursive parentheses

int		match_paren(char *s, char **dollar_sign, char **closing_paren)
{
//	char *last_valid_dollar;

//	last_valid_dollar = NULL;
	*dollar_sign = s;
	while (*dollar_sign && (*dollar_sign = ft_strstr(*dollar_sign, "$(")) != NULL)
	{
		if ((*dollar_sign == s || *(*dollar_sign - 1) != '\\') &&
		(*closing_paren = ft_strchr(*dollar_sign, ')')) && *(*closing_paren - 1) != '\\')
				return (1);
		(*dollar_sign)++;
	}
	return (0);
//	return (last_valid_dollar ? 1 : 0);
}

int		expand_cmdsub(char *s, char **new_s)
{
	char *ptr;
	char *closing_paren;

	if (s[0] == '\'')
		return (0);
	else if (match_bquotes(s, &ptr) == 1)
		return (bquotes_exp(s, ptr, new_s));
	else if (match_paren(s, &ptr, &closing_paren) == 1)
		return(paren_exp(s, ptr, closing_paren, new_s));

	return (0);
}

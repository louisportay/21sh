/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmdsub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:09:20 by lportay           #+#    #+#             */
/*   Updated: 2018/04/20 16:06:40 by lportay          ###   ########.fr       */
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
	size_t	used_brefore_write;

	close(fd[1]);
	used_brefore_write = qbuf->used;
	while ((sz = read(fd[0], buf, BUFF_SIZE)) != 0)
		qbuf_addn(qbuf, buf, sz);
	if (qbuf->buffer[0] != '"')
		remove_nl(qbuf->buffer);
	if (qbuf->used > used_brefore_write)
		qbuf->used--;
	qbuf_add(qbuf, c_char);
}

/*
**	char *closing_paren;
**
**	else if (match_paren(s, &ptr, &closing_paren) == 1)
**		return(paren_exp(s, ptr, closing_paren, new_s));
*/

int		expand_cmdsub(char *s, char **new_s)
{
	char *ptr;

	if (s[0] == '\'')
		return (0);
	else if (match_bquotes(s, &ptr) == 1)
		return (bquotes_exp(s, ptr, new_s));
	else
		return (0);
}

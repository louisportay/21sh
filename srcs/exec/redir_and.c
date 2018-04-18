/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 22:14:47 by lportay           #+#    #+#             */
/*   Updated: 2018/04/18 15:16:23 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int				r_andgreat_anddgreat(t_redir *r)
{
	int fd;

	if ((fd = open(r->s_rhs, O_WRONLY | O_CREAT | ((r->type & ANDGREAT) ?
														O_TRUNC : O_APPEND),
															0644)) == -1)
		return (err_open(r->s_rhs));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (err_close_fd(fd));
	if (dup2(fd, STDERR_FILENO) == -1)
		return (err_close_fd(fd));
	close(fd);
	return (0);
}

static int		err_ambig_redir(char *s)
{
	ft_dprintf(STDERR_FILENO, "42sh: %s: ambiguous redirect\n", s);
	return (-1);
}

static int		get_right_op(t_redir *tok)
{
	if (is_number(tok->s_rhs) == true)
		tok->fd_rhs = ft_atoi(tok->s_rhs);
	else if (*tok->s_rhs == '-' && ft_strlen(tok->s_rhs) == 1)
		tok->dash = true;
	else if (is_number_w_dash(tok->s_rhs) == true)
	{
		tok->fd_rhs = ft_atoi(tok->s_rhs);
		tok->dash = true;
	}
	else
		return (-1);
	return (0);
}

int				r_greatand_lessand(t_redir *r, int fd[3], int *pipes, int ipc)
{
	if (get_right_op(r) == -1)
		return (err_ambig_redir(r->s_rhs));
	else if (r->fd_rhs == fd[0] || r->fd_rhs == fd[1] || r->fd_rhs == fd[2])
		return (err_busyfd(r->fd_rhs));
	else if (pipes != NULL && r->fd_rhs != -1
				&& (pipes[0] == r->fd_rhs || pipes[1] == r->fd_rhs))
		return (err_busyfd(r->fd_rhs));
	else if (ipc != -1 && r->fd_rhs == ipc)
		return (err_busyfd(r->fd_rhs));
	if (r->fd_rhs != -1 && r->fd_rhs == r->lhs)
		return (0);
	if (r->fd_rhs != -1 && dup2(r->fd_rhs, r->lhs) == -1)
		return (err_badfd(r->s_rhs));
	if (r->dash == true && r->fd_rhs != -1)
		close(r->fd_rhs);
	else if (r->dash == true)
		close(r->lhs);
	return (0);
}

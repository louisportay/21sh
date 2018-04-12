/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:07:55 by lportay           #+#    #+#             */
/*   Updated: 2018/04/12 16:12:09 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		r_great_dgreat(t_redir *r)
{
	int fd;

	if ((fd = open(r->s_rhs, O_WRONLY | O_CREAT | ((r->type & GREAT)
													? O_TRUNC : O_APPEND),
					0644)) == -1)
		return (err_open(r->s_rhs));
	if (dup2(fd, r->lhs) == -1)
		return (err_close_fd(fd));
	close(fd);
	return (0);
}

int		r_less(t_redir *r)
{
	int fd;

	if ((fd = open(r->s_rhs, O_RDONLY)) == -1)
		return (err_open(r->s_rhs));
	if (dup2(fd, r->lhs) == -1)
		return (err_close_fd(fd));
	close(fd);
	return (0);
}

int		r_dless_tless(t_redir *r)
{
	int		fd;

	if ((fd = ft_tmpfile()) == -1)
		return (err_tmpfile());
	if (write(fd, r->s_rhs, ft_strlen(r->s_rhs)) == -1)
		return (err_close_fd(fd));
	if (lseek(fd, 0, SEEK_SET) == -1)
		return (err_close_fd(fd));
	if (dup2(fd, r->lhs) == -1)
		return (err_close_fd(fd));
	close(fd);
	return (0);
}

int		do_redir(t_redir *r, int fd[3], int *pipes)
{
	int ret;

	while (r)
	{
		if (r->lhs == fd[0] || r->lhs == fd[1] || r->lhs == fd[2])
			return (err_busyfd(r->lhs));
		else if (pipes != NULL && (pipes[0] == r->lhs || pipes[1] == r->lhs))
			return (err_busyfd(r->lhs));
		if (r->type & (GREAT | DGREAT))
			ret = r_great_dgreat(r);
		else if (r->type & LESS)
			ret = r_less(r);
		else if (r->type & (DLESS | TLESS))
			ret = r_dless_tless(r);
		else if (r->type & R_AND)
			ret = r_andgreat_anddgreat(r);
		else if (r->type & (GREATAND | LESSAND))
			ret = r_greatand_lessand(r, fd, pipes);
		else
			return (-1);
		if (ret == -1)
			return (ret);
		r = (t_redir *)r->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:07:55 by lportay           #+#    #+#             */
/*   Updated: 2018/04/22 20:10:25 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	clear_lfd(int lfd[7])
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (lfd[i])
			close(i + 3);
		i++;
	}
}

int		r_great_dgreat(t_redir *r, int lfd[7])
{
	int fd;

	if ((fd = open(r->s_rhs, O_WRONLY | O_CREAT | ((r->type & GREAT)
													? O_TRUNC : O_APPEND),
					0644)) == -1)
		return (err_open(r->s_rhs));
	if (dup2(fd, r->lhs) == -1)
		return (err_close_fd(fd));
	close(fd);
	if (r->lhs > 2)
		lfd[r->lhs - 3] = 1;
	return (0);
}

int		r_less(t_redir *r, int lfd[7])
{
	int fd;

	if ((fd = open(r->s_rhs, O_RDONLY)) == -1)
		return (err_open(r->s_rhs));
	if (dup2(fd, r->lhs) == -1)
		return (err_close_fd(fd));
	close(fd);
	if (r->lhs > 2)
		lfd[r->lhs - 3] = 1;
	return (0);
}

int		r_dless_tless(t_redir *r, int lfd[7])
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
	if (r->lhs > 2)
		lfd[r->lhs - 3] = 1;
	return (0);
}

int		do_redir(t_redir *r, int fd[7])
{
	int ret;

	while (r)
	{
		if (r->lhs >= 10)
			return (err_busyfd(r->lhs));
		if (r->type & (GREAT | DGREAT))
			ret = r_great_dgreat(r, fd);
		else if (r->type & LESS)
			ret = r_less(r, fd);
		else if (r->type & (DLESS | TLESS))
			ret = r_dless_tless(r, fd);
		else if (r->type & R_AND)
			ret = r_andgreat_anddgreat(r);
		else if (r->type & (GREATAND | LESSAND))
			ret = r_greatand_lessand(r, fd);
		else
			return (-1);
		if (ret == -1)
			return (ret);
		r = (t_redir *)r->next;
	}
	return (0);
}

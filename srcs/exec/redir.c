/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:07:55 by lportay           #+#    #+#             */
/*   Updated: 2018/03/26 16:50:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		get_right_op(t_redir *tok)
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

int		err_close_fd(int fd)
{
	close(fd);
	return (-1);
}

int		err_open(char *s)
{
	dprintf(STDERR_FILENO, "21sh: %s: No such file or directory\n", s);
	return (-1);
}

int		err_ambig_redir(char *s)
{
	dprintf(STDERR_FILENO, "21sh: %s: ambiguous redirect\n", s);
	return (-1);
}

int		err_tmpfile(void)
{
	dprintf(STDERR_FILENO, "21sh: error creating temporary file\n");
	return (-1);
}

int		r_great_dgreat(t_redir *r)
{
	int fd;

	if ((fd = open(r->s_rhs, O_WRONLY | O_CREAT | ((r->type & GREAT) ? O_TRUNC : O_APPEND), 0644)) == -1)
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

	if (!r->s_rhs)//
		return (-1);// A enlever et a checker en amont

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

int		r_andgreat_anddgreat(t_redir *r)
{
	int fd;

	if ((fd = open(r->s_rhs, O_WRONLY | O_CREAT | ((r->type & ANDGREAT) ? O_TRUNC : O_APPEND), 0644)) == -1)
		return (err_open(r->s_rhs));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (err_close_fd(fd));
	if (dup2(fd, STDERR_FILENO) == -1)
		return (err_close_fd(fd));
	close(fd);
	return (0);
}

int		r_greatand_lessand(t_redir *r)
{
	if (get_right_op(r) == -1)
		return (err_ambig_redir(r->s_rhs));
	if (r->fd_rhs != -1 && dup2(r->fd_rhs, r->lhs) == -1)
			return (-1);
	if (r->dash == true && r->fd_rhs != -1)
		close(r->fd_rhs);
	else if (r->dash == true)
		close(r->lhs);
	return (0);
}

int		do_redir(t_redir *r)
{
	int ret;

	while (r)
	{
		if (r->type & (GREAT | DGREAT))
			ret = r_great_dgreat(r);
		else if (r->type & LESS)
			ret = r_less(r);
		else if (r->type & (DLESS | TLESS))
			ret = r_dless_tless(r);
		else if (r->type & R_AND)
			ret = r_andgreat_anddgreat(r);
		else if (r->type & (GREATAND | LESSAND))
			ret = r_greatand_lessand(r);
		else
			return (-1);
		if (ret == -1)
			return (ret);
		r = (t_redir *)r->next;
	}
	return (0);
}

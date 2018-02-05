/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:07:55 by lportay           #+#    #+#             */
/*   Updated: 2018/02/05 23:02:30 by lportay          ###   ########.fr       */
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

int		r_great_dgreat(t_redir *r)
{
	int tmp;

	if ((tmp = open(r->s_rhs, O_WRONLY | O_CREAT | ((r->type & GREAT) ? O_TRUNC : O_APPEND), 0644)) == -1)
		return (tmp);
	if (dup2(tmp, r->lhs) == -1)
		return (-1);
	close(tmp);
	return (0);
}

int		r_less(t_redir *r)
{
	int tmp;

	if ((tmp = open(r->s_rhs, O_RDONLY)) == -1)
		return (tmp);
	if (dup2(tmp, r->lhs) == -1)
		return (-1);
	close(tmp);
	return (0);
}

int		r_dless(t_redir *r)
{
	(void)r;//
	t_21sh *env;
	
	env = get_envaddr(NULL);
	env->heredoc_eof = r->rhs;
	wrap_lineread(env, r->hdoc, PS2);
	env->heredoc_eof = NULL;
//faire la redirection tout ca + free le heredoc
	return (0);
}

int		r_tless(t_redir *r)
{
	char	*filepath;
	time_t	t;
	int		tmpfile;

	t = time(NULL);
	filepath = fullpath("/tmp", ctime(&t));
	if ((tmpfile = open(filepath, O_WRONLY | O_EXCL | O_CREAT, 0600)) == -1)
		return (tmpfile);
	write(tmpfile, r->s_rhs, ft_strlen(r->s_rhs) + 1);
	close(tmpfile);
	if ((tmpfile = open(filepath, O_RDONLY)) == -1)
		return (tmpfile);
	unlink(filepath);
	free(filepath);
	if (dup2(tmpfile, r->lhs) == -1)
		return (-1);
	close(tmpfile);
	return (0);
}

int		r_andgreat_anddgreat(t_redir *r)
{
	int tmp;

	if ((tmp = open(r->s_rhs, O_WRONLY | O_CREAT | ((r->type & ANDGREAT) ? O_TRUNC : O_APPEND), 0644)) == -1)
		return (tmp);
	if (dup2(tmp, STDOUT_FILENO) == -1)
		return (-1);
	if (dup2(tmp, STDERR_FILENO) == -1)
		return (-1);
	close(tmp);
	return (0);
}

int		r_greatand_lessand(t_redir *r)
{
	if (get_right_op(r) == -1)
	{
		ft_putstr(AMBIG_REDIR);
		return (-1);
	}
	if (r->fd_rhs != -1)
		if (dup2(r->fd_rhs, r->lhs) == -1)
			return (-1);
	if (r->dash == true && r->fd_rhs != -1)
		close(r->fd_rhs);
	else if (r->dash == true)
		close(r->lhs);
	return (0);
}

int		do_redir(t_redir *r)
{
	if (r->type & (GREAT | DGREAT))
		return (r_great_dgreat(r));
	else if (r->type & LESS)
		return (r_less(r));
	else if (r->type & DLESS)
		return (r_dless(r));
	else if (r->type & TLESS)
		return (r_tless(r));
	else if (IS_AND_REDIR(r->type))
		return (r_andgreat_anddgreat(r));
	else if (r->type == (GREATAND | LESSAND))
		return (r_greatand_lessand(r));
	else
		return (-1);
}

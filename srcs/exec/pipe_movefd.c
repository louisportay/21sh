/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_movefd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 20:21:01 by lportay           #+#    #+#             */
/*   Updated: 2018/04/22 20:21:28 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void				do_move_fd(int *pipes, int fd)
{
	dup2(pipes[0], fd);
	close(pipes[0]);
	pipes[0] = fd;
}

void					move_fd_up(int *pipes)
{
	if (pipes[2] != LOWER_PIPE_BND && pipes[3] != LOWER_PIPE_BND)
	{
		do_move_fd(pipes, LOWER_PIPE_BND);
		return ;
	}
	if ((pipes[2] == LOWER_PIPE_BND && pipes[3] == -1)
		|| (pipes[3] == LOWER_PIPE_BND && pipes[2] == -1))
		do_move_fd(pipes, LOWER_PIPE_BND + 1);
	else if (pipes[2] == LOWER_PIPE_BND && pipes[3] > pipes[2])
		do_move_fd(pipes, pipes[3] + 1);
	else if (pipes[3] == LOWER_PIPE_BND && pipes[2] > pipes[3])
		do_move_fd(pipes, pipes[2] + 1);
	else
	{
		ft_putstr_fd("42sh: Big fd assignment error\n", STDERR_FILENO);
		wrap_exit(-42, get_ctxaddr());
	}
}

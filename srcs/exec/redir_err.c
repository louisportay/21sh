/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 22:12:39 by lportay           #+#    #+#             */
/*   Updated: 2018/04/12 16:25:53 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		err_close_fd(int fd)
{
	close(fd);
	return (-1);
}

int		err_open(char *s)
{
	ft_dprintf(STDERR_FILENO, "21sh: %s: No such file or directory\n", s);
	return (-1);
}

int		err_busyfd(int fd)
{
	ft_dprintf(STDERR_FILENO, "21sh: %d: Bad file descriptor\n", fd);
	return (-1);
}

int		err_tmpfile(void)
{
	ft_dprintf(STDERR_FILENO, "21sh: error creating temporary file\n");
	return (-1);
}

int		err_badfd(char *fd)
{
	ft_dprintf(STDERR_FILENO, "21sh: %s: Bad file descriptor\n", fd);
	return (-1);
}

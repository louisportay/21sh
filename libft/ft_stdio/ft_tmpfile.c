/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmpfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:50:50 by lportay           #+#    #+#             */
/*   Updated: 2018/02/15 17:55:21 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

int		ft_tmpfile(void)
{
	char	*name;
	int		fd;
	int		i;

	i = 0;
	if (!(name = ft_itoa(i)))
			return (-1);
	while ((fd = open(name, O_RDWR | O_EXCL | O_CREAT, 0644)) == -1
			&& i++ < INT_MAX)
	{
		free(name);
		if (!(name = ft_itoa(i)))
			return (-1);
	}
	if (fd != -1)
		unlink(name);
	free(name);
	return (fd);
}

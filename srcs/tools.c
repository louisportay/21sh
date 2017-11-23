/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 10:48:13 by lportay           #+#    #+#             */
/*   Updated: 2017/11/20 10:48:36 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** function written for tputs to output the characters
*/

int		ft_putchar_stdin(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (c);
}
